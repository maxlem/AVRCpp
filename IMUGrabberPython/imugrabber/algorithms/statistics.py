'''
Created on 2009-07-27

@author: malem-cnc
'''

import math
import scipy as sp
import collections

def frange(start, stop, steps):
    listOfValues = [0.0] * steps
    numberOfValues = steps - 1
    numberOfValuesInverse = 1.0 / numberOfValues
    for i in range(steps):
        listOfValues[i] = numberOfValuesInverse * (start*(numberOfValues - i) + stop*i)
    return listOfValues

def samplesMeanStandardDeviation(samplesByLabels):
    
    statisticsByLabel = collections.defaultdict(list)
    
    for label, samples in samplesByLabels.iteritems() :
        
        sampleSum = 0.0
        
        for sample in samples :
            sampleSum += sample
        
        samplesCount = len(samples)
        
        populationMean = sampleSum/samplesCount
        
        squaredDistanceFromMeanSum = 0.0
        
        for sample in samples :
            squaredDistanceFromMeanSum += (sample - populationMean)**2
        
        populationStdDev = math.sqrt(squaredDistanceFromMeanSum/(samplesCount-1))
        
        statisticsByLabel[label] = (populationMean, populationStdDev)
        
    return statisticsByLabel

def normalize_against_z(x, y, z):
    maxZ = max(z)
    minZ = min(z)
    zeroG = minZ + (maxZ - minZ) / 2.0
    scaleG = maxZ - zeroG
    
    zeroGArray =  sp.ones_like(z) * zeroG
    
    normalized = []
    for axis in (x, y, z) :
        axisArray = sp.r_[axis]
        axisArray -= zeroGArray
        axisArray /= scaleG
        normalized.append(axisArray.tolist())
    
    return tuple(normalized)
    
    
    
    
            
    
