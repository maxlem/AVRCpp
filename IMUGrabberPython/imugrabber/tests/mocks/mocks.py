'''
Created on 2009-08-18

@author: malem303
'''
import collections
import struct
from imugrabber.algorithms import statistics

def trainingDataSet(longitudeRange = (-5.0, 5.0, 10), latitudeRange = (-5.0, 5.0, 10)):

    
    trainingDataSet = collections.defaultdict(list)
    
    for longitude in statistics.frange(*longitudeRange) :
        for latidute in statistics.frange(*latitudeRange) :
            trainingDataSet[(longitude, latidute)] = samplesByLabels({'x' : (longitude*.1, latidute*.1, 10), 'y' : (longitude*.2, latidute*.2, 10), 'z' : (longitude*.4, latidute*.4, 10)})
    
    return trainingDataSet


def samplesByLabels(samplesRangeBylabel = {'x' : (5.0, 15.0, 10), 'y' : (0.0, 10.0, 10), 'z' : (25.0, 55.0, 10)}):
    
    samplesByLabels = collections.defaultdict(list)
    
    for label, samplesRange in samplesRangeBylabel.iteritems() :
        for sample in statistics.frange(*samplesRange) :
            samplesByLabels[label].append(sample)
    return samplesByLabels

