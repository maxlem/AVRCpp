'''
Created on 2010-04-29

@author: malem303
'''

from imugrabber.algorithms import statistics, utils, io
from threading import Thread
import time
_timescale = (64.0/16.0e6)
class AcquisitionThread(Thread):
    '''
    classdocs
    '''


    def __init__(self, observer, acquisition, filter, refreshRateHertz = 24.0):
        '''
        Constructor
        '''
        Thread.__init__(self)
        
        self.filter = filter
        self.observer = observer
        self.acquisition = acquisition
        self.refreshRateHertz = refreshRateHertz
        self.lastReading = []
        
        statisticsByLabelBeforeMotion = statistics.samplesMeanStandardDeviation(self.acquisition.acquireSamplesDuring(1.0))
        
        self.gyroBias = [statisticsByLabelBeforeMotion['a'][0], statisticsByLabelBeforeMotion['b'][0], statisticsByLabelBeforeMotion['c'][0]]
        self.gyroMisalignmentsAndScales, x, x = io.deserialize_results(io._pkl_path, "gyro_params_latest.pkl")
        
        self.accMisalignmentsAndScales, self.accBias = io.deserialize_results(io._pkl_path, "accelero_params_latest.pkl")
        self.accBias = self.accBias.reshape(3).tolist()
        
        self.timestampBias = statisticsByLabelBeforeMotion['s'][0]
        
        #[self.statisticsByLabelBeforeMotion['x'][0], self.statisticsByLabelBeforeMotion['y'][0], self.statisticsByLabelBeforeMotion['z'][0]] 
        
    def run(self):
        while True:
            self._update()
            time.sleep(1.0/self.refreshRateHertz)
#            self._checkLastCommandSerialNumber()
        
    def _update(self):
        
        self.acquisition.flushBuffer()
        samplesByLabel = self.acquisition.acquireNSamples(1, "abcxyzs")
        
        accMeasure = [samplesByLabel['x'][0], samplesByLabel['y'][0], samplesByLabel['z'][0]] 
        gyroMeasure = [samplesByLabel['a'][0], samplesByLabel['b'][0], samplesByLabel['c'][0]]
        
    
        gyroMeasure = utils.correct_measure(self.gyroMisalignmentsAndScales, self.gyroBias, gyroMeasure).tolist()
        accMeasure = utils.correct_measure(self.accMisalignmentsAndScales, self.accBias, accMeasure).tolist()
    
#        print accMeasure
        timestamp = (samplesByLabel['s'][0] - self.timestampBias) * _timescale 
        
        measure = accMeasure
        measure.extend(gyroMeasure)
        self.filter.filter(timestamp, measure)
        
        state = self.filter.stateMean()
        
        self.observer.position = state[0:3]
        
        print accMeasure
        
        
        
        