'''
Created on 2009-08-11

@author: malem303
'''
import math
import scipy as sp
from scipy import optimize, interpolate

from imugrabber.algorithms import utils, scipy_utils, statistics

def computeTargetVelocities(targetKnots, imuTimestamps):
    aSplineTCK, bSplineTCK = targetKnots
    
    bTargetPositions = interpolate.splev(imuTimestamps, bSplineTCK, der = 0)
        
    aTargetVelocities = interpolate.splev(imuTimestamps, aSplineTCK, der = 1)
        
    bTargetVelocities = interpolate.splev(imuTimestamps, bSplineTCK, der = 1)
    
    targetVelocities = sp.zeros((len(imuTimestamps), 3))
    
    
    for index in range(len(imuTimestamps)) :
    
        targetVelocities[index,:] = sp.dot(scipy_utils.pitch_transform(bTargetPositions[index]), 
                                           sp.array([aTargetVelocities[index], 0, 0])) + sp.array([0, bTargetVelocities[index], 0])

    return targetVelocities

def objectiveFunction(parameters, targetKnots, statisticsByLabelBeforeMotion, samplesByLabelInMotion):
    
    gyroMisalignmentsAndScales = sp.reshape(parameters[0:9], (3, 3))
    
    correctedMeasures = sp.transpose(utils.extract_and_correct_gyro_motion(gyroMisalignmentsAndScales, statisticsByLabelBeforeMotion, samplesByLabelInMotion))
    
    
    imuSamplesCount = len(samplesByLabelInMotion['timestamps'])
    correctedMeasures = correctedMeasures[0:imuSamplesCount:3]
    
    skew, shift = parameters[9], parameters[10]
    imuTimestamps = sp.array(samplesByLabelInMotion['timestamps'])[0:imuSamplesCount:3] * skew
    imuTimestamps += sp.ones_like(imuTimestamps) * shift
    
    targetVelocities = computeTargetVelocities(targetKnots, imuTimestamps)
                                
    residualVectors = targetVelocities - correctedMeasures
    residuals = residualVectors * residualVectors
    residuals = sp.sqrt(residuals[:,0] + residuals[:,1] + residuals[:,2])
    
    
    print sp.dot(residuals, residuals)
        
    return sp.sqrt(sp.dot(residuals, residuals))


def buildGyroRanges(idg1215scale, lisy300scale, gyroMargin):
    idg1215range = (idg1215scale * (1 - gyroMargin), idg1215scale * (1 + gyroMargin))
    lisy300range = (lisy300scale * (1 - gyroMargin), lisy300scale * (1 + gyroMargin))
    crossAxisRanges = (- (gyroMargin**2) * idg1215scale, (gyroMargin**2) * idg1215scale)
    return crossAxisRanges, lisy300range, idg1215range


def assembleRanges(crossAxisRanges, lisy300range, idg1215range, skewRange, shiftRange):
    ranges = [idg1215range, crossAxisRanges, crossAxisRanges, crossAxisRanges, idg1215range, crossAxisRanges, 
        crossAxisRanges, crossAxisRanges, lisy300range, 
        skewRange, shiftRange]
    return ranges

def buildPriors():
    idg1215scale = math.radians(67.0) / ((2.8 / 3.3) * 512.0) * 1.5
    lisy300scale = math.radians(300.0) / 512.0 * 1.5
    skew, shift = .98, -10.0
    parameters = sp.array([idg1215scale, 0, 0, 
            0, idg1215scale, 0, 
            0, 0, lisy300scale, 
            skew, shift])
    
    return idg1215scale, lisy300scale, skew, shift, parameters

def buildRangesForShiftSkew(idg1215scale, lisy300scale, skew, shift):

    gyroMargin = 1e-8
    
    skewRange, shiftRange = (skew - .05, skew + .05), (shift - .5, shift + .5)
    
    crossAxisRanges, lisy300range, idg1215range = buildGyroRanges(idg1215scale, lisy300scale, gyroMargin)
    
    return assembleRanges(crossAxisRanges, lisy300range, idg1215range, skewRange, shiftRange)

def buildRangesForMisalignmentsAndScales(idg1215scale, lisy300scale, skew, shift):

    gyroMargin = 0.5
    
    skewRange, shiftRange = (skew - 1e-7, skew + 1e-7), (shift - 1e-3, shift + 1e-3)
    
    crossAxisRanges, lisy300range, idg1215range = buildGyroRanges(idg1215scale, lisy300scale, gyroMargin)
    
    return assembleRanges(crossAxisRanges, lisy300range, idg1215range, skewRange, shiftRange)

def fit(targetKnots, dataSet):
    
    samplesByLabelBeforeMotion, samplesByLabelInMotion = dataSet
    statisticsByLabelBeforeMotion = statistics.samplesMeanStandardDeviation(samplesByLabelBeforeMotion)
    
    idg1215scale, lisy300scale, skew, shift, parameters = buildPriors()
    
    ranges = buildRangesForShiftSkew(idg1215scale, lisy300scale, skew, shift)
    
    parameters, f, d = optimize.fmin_l_bfgs_b(func = objectiveFunction, x0 = parameters, bounds = ranges, args = (targetKnots, statisticsByLabelBeforeMotion, samplesByLabelInMotion), approx_grad = True, maxfun = 50, epsilon = 1e-8)
    
    skew, shift = parameters[9], parameters[10]
    
    ranges = buildRangesForShiftSkew(idg1215scale, lisy300scale, skew, shift)
    
    parameters, f, d = optimize.fmin_l_bfgs_b(func = objectiveFunction, x0 = parameters, bounds = ranges, args = (targetKnots, statisticsByLabelBeforeMotion, samplesByLabelInMotion), approx_grad = True, maxfun = 10, epsilon = 1e-5)
    
    misalignmentsAndScales = sp.reshape(parameters[0:9], (3, 3))
    
    skew, shift = parameters[9], parameters[10]
    
    return misalignmentsAndScales, skew, shift
    
