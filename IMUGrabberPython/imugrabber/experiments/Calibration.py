'''
Created on 2009-05-26

@author: malem303

def _log_exploration(longitude, latitude, samplesByLabel, label):
    samples, timestamps = zip(samplesByLabel[label])
    print "axis %c, pos (%f, %f), mean %f \n" % (label, longitude, latitude, mlab.mean(samples))

'''
import collections
import math
import time
import scipy as sp
from imugrabber.algorithms import statistics, utils
from imugrabber.algorithms import io
from imugrabber.experiments import plots

_FEED_RATE = 2000.0
_GCODE = "G1"
_SAMPLES_PER_POSITION = 10
_EPSILON_FINE_TUNE = 0.0000001
_MIN_MACHINE_STEP = 0.0001

class Calibration(object):
    
    def __init__(self, acquisition, machine, longitudeGCodeLabel, latitudeGCodeLabel):
        
        self.acquisition = acquisition
        self.machine = machine
        self.longitudeGCodeLabel = longitudeGCodeLabel.upper()
        self.latitudeGCodeLabel = latitudeGCodeLabel.upper()
        self.machine.interpreter.mdi("F%f" % (_FEED_RATE))
        self.movementCount = 0

    def _moveSingleDOF(self, gCodeLabel, newPosition, waitCompletion = True):
        
        self.machine.interpreter.mdi("%s %c%f" % (_GCODE, gCodeLabel, newPosition), waitCompletion)
 
    def _moveTwoDOF(self, gCodeLabel1, newPosition1, gCodeLabel2, newPosition2, waitCompletion = True):
        
        self.machine.interpreter.mdi("%s %c%f %c%f" % (_GCODE, gCodeLabel1, newPosition1, gCodeLabel2, newPosition2), waitCompletion)
              
    def _gradientAscent(self, samplingLabelToMaximize, stepWitdh, gVectorStartPosition, startValue):
        
        self._moveTwoDOF(self.longitudeGCodeLabel, gVectorStartPosition[0], self.latitudeGCodeLabel, gVectorStartPosition[1])
        current = startValue
        previous = 99999e99
        while abs(current - previous) > _EPSILON_FINE_TUNE:
            
            previous = current

            current = self._gradientStep(self.longitudeGCodeLabel, stepWitdh, samplingLabelToMaximize)
            current = self._gradientStep(self.latitudeGCodeLabel, stepWitdh, samplingLabelToMaximize)
            
            if(abs(current - previous) > _MIN_MACHINE_STEP):
                stepWitdh = abs(current - previous)
            
            print "%s is %f, previous was %f" % (samplingLabelToMaximize, current, previous)
        
        gVectorPosition = self.machine.joints[self.longitudeGCodeLabel].position, self.machine.joints[self.latitudeGCodeLabel].position
        return gVectorPosition, current
    
    def _exhaustiveSearch(self, samplingLabelToMaximize, dofExplorationRange):
        
        trainingDataSet = self.exploreUnitSphere(dofExplorationRange, dofExplorationRange)
        
        currentLargest = 0
        gVectorPosition = (0.0, 0.0)
        meansSum = 0.0
        meansSquaredSum = 0.0
        meansCount = 0
        for position, samplesByLabel in trainingDataSet.iteritems():
            statisticsByLabel = statistics.samplesMeanStandardDeviation(samplesByLabel)
            mean, std = statisticsByLabel[samplingLabelToMaximize]
            mean = abs(mean)
            meansSum += mean
            meansSquaredSum += mean ** 2.0
            meansCount += 1
            if mean > currentLargest:
                currentLargest = mean
                gVectorPosition = position
            
        
        return gVectorPosition, currentLargest
    
    def findMaxPosition(self, samplingLabelToMaximize, dofExplorationRange = statistics.frange(-5.0, 5.0, 10), fineTuningStepWidth = 0.1):
    
        
        gVectorPosition, maximum = self._exhaustiveSearch(samplingLabelToMaximize, dofExplorationRange)
        
        maxima = (gVectorPosition, maximum), self._gradientAscent(samplingLabelToMaximize, fineTuningStepWidth, gVectorPosition, maximum)
        
        return maxima
            
    
    def _acquireAtPosition(self, dofGCodeLabel, newPosition, samplingLabelToMaximize):
        
        self._moveSingleDOF(dofGCodeLabel, newPosition)
        statisticsByLabel = statistics.samplesMeanStandardDeviation(self.acquisition.acquireNSamples(_SAMPLES_PER_POSITION, samplingLabelToMaximize))
        mean, std = statisticsByLabel[samplingLabelToMaximize]
        return abs(mean)
    
    def _gradientStep(self, dofGCodeLabel, stepWidth, samplingLabelToMaximize):
        
        dofPosition = self.machine.joints[dofGCodeLabel].position
        
        currentMinusEpsilon = self._acquireAtPosition(dofGCodeLabel, (dofPosition - stepWidth), samplingLabelToMaximize)
        
        currentPlusEpsilon = self._acquireAtPosition(dofGCodeLabel, (dofPosition + stepWidth), samplingLabelToMaximize)
        
        current = self._acquireAtPosition(dofGCodeLabel, dofPosition, samplingLabelToMaximize)
          
        maximum = max(currentMinusEpsilon, current, currentPlusEpsilon)
        
        cases = {currentMinusEpsilon : lambda : self._moveSingleDOF(dofGCodeLabel, dofPosition - stepWidth),
                 current : lambda : self._moveSingleDOF(dofGCodeLabel, dofPosition),
                 currentPlusEpsilon : lambda : self._moveSingleDOF(dofGCodeLabel, dofPosition + stepWidth)}
        
        cases[maximum]()
        
        return maximum
            
        
    def exploreUnitSphere(self, longitudes, latitudes):
        
        trainingDataSet = collections.defaultdict(list)
    
        latitudes = list(latitudes)
    
        for longitude in longitudes:
            self._moveSingleDOF(self.longitudeGCodeLabel, longitude)
    
            for latitude in latitudes:
                self._moveSingleDOF(self.latitudeGCodeLabel, latitude)
                
                self.acquisition.flushBuffer()
                
                longitude = self.machine.joints[self.longitudeGCodeLabel].position
                latitude = self.machine.joints[self.latitudeGCodeLabel].position
                
                trainingDataSet[(longitude, latitude)] = self.acquisition.acquireNSamples(_SAMPLES_PER_POSITION, "xyz")
                
            latitudes = list(reversed(latitudes))
                
                
        return trainingDataSet
    
    
    def fongGyroMotion(self, startPosition = (-5, 0), stopPosition = (5,0), feedrate = _FEED_RATE, staticSamplingDelay = 1.0, motionDuration = 5.0):
        
#        self.acquisition.changePattern()   
        
        self.machine.interpreter.mdi("F%f" % (feedrate))
        
        self._moveTwoDOF(self.longitudeGCodeLabel, startPosition[0], self.latitudeGCodeLabel, startPosition[1])
        
        startPosition = self.machine.joints[self.longitudeGCodeLabel].position, self.machine.joints[self.latitudeGCodeLabel].position
        
        self.acquisition.flushBuffer()
        
        samplesByLabelBeforeMotion = self.acquisition.acquireSamplesDuring(staticSamplingDelay)
        
        self.acquisition.flushBuffer()
        
        beginTime = float(self.machine.getPin("timestamp", 0, "out"))
        
        self._moveTwoDOF(self.longitudeGCodeLabel, stopPosition[0], self.latitudeGCodeLabel, stopPosition[1], False)
        
        samplesByLabelInMotion = self.acquisition.acquireSamplesDuring(motionDuration)
        
        endTime = float(self.machine.getPin("timestamp", 0, "out"))
        
        stopPosition = self.machine.joints[self.longitudeGCodeLabel].position, self.machine.joints[self.latitudeGCodeLabel].position
        
        self.acquisition.flushBuffer()
        
        samplesCount = 0
        for label, samples in samplesByLabelInMotion.iteritems() :
            samplesCount += len(samples)
            
        samplesByLabelAfterMotion = self.acquisition.acquireNSamples(100)
        
        print "movement numer %d, %d samples" % (self.movementCount, samplesCount)
        self.movementCount += 1
        
        samplesByLabelInMotion['timestamps'] = list(sp.array(samplesByLabelInMotion['s'], dtype=sp.double) * 64.0/16e6)
    
        plots.plot_samplesByLabel(samplesByLabel = samplesByLabelInMotion, xAxisLabel = 'timestamps', labelsToExclude = ['x', 'y', 'z', 's', 't', 'timestamps', 'T'], figure = self.movementCount)
        
        io.save_current_figure("raw%d.pdf" % self.movementCount)
        
        return (startPosition, stopPosition, feedrate, beginTime, endTime), statistics.samplesMeanStandardDeviation(samplesByLabelBeforeMotion), samplesByLabelInMotion, statistics.samplesMeanStandardDeviation(samplesByLabelAfterMotion)

    
