'''
Created on 2009-08-11

@author: malem303
'''

import scipy as sp
from scipy import optimize
from cgkit.cgtypes import quat
import math

from imugrabber.algorithms import utils

def residual(parameters, motion, statisticsByLabelBeforeMotion, samplesByLabelInMotion, statisticsByLabelAfterMotion, acceleroMisalignmentsAndScales, acceleroBias):
    
#    gravityVectorBefore = sp.array([statisticsByLabelBeforeMotion['x'][0], statisticsByLabelBeforeMotion['y'][0], statisticsByLabelBeforeMotion['z'][0]])
#
#    gravityVectorBefore = utils.correct_measures(acceleroMisalignmentsAndScales, acceleroBias, gravityVectorBefore.reshape((3,1)))
#    
#    gravityVectorAfter = sp.array([statisticsByLabelAfterMotion['x'][0], statisticsByLabelAfterMotion['y'][0], statisticsByLabelAfterMotion['z'][0]])
#  
#    gravityVectorAfter = utils.correct_measures(acceleroMisalignmentsAndScales, acceleroBias, gravityVectorAfter.reshape((3,1)))
    
    gyroMisalignmentsAndScales = sp.reshape(parameters, (3, 3))
    
    correctedMeasures = utils.extract_and_correct_gyro_motion(gyroMisalignmentsAndScales, statisticsByLabelBeforeMotion, samplesByLabelInMotion)
    
    aSamples, bSamples, cSamples = correctedMeasures[0,:], correctedMeasures[1,:], correctedMeasures[2,:]
    
#    gravityVector = vec3(*sp.reshape(gravityVectorBefore, 3))

    fromAngularPosition, toAngularPosition, feedrate, endTime, beginTime = motion
    
    gravityVector = utils.gravityVector_IMU_coords(math.radians(fromAngularPosition[0]), math.radians(fromAngularPosition[1]))
    
    gravityVectorAfter = utils.gravityVector_IMU_coords(math.radians(toAngularPosition[0]), math.radians(toAngularPosition[1]))
    
    timestamps = samplesByLabelInMotion['timestamps']
    
    previousTimestamp = timestamps[0]
    
    for index in range(len(timestamps)) :
        
        angularVelocityQuat = quat(0.0, aSamples[index], bSamples[index], cSamples[index])
        
        timeElapsed = timestamps[index] - previousTimestamp
            
        previousTimestamp = timestamps[index]
        
        gravityVector = (angularVelocityQuat * timeElapsed / 2).exp().rotateVec(gravityVector)
    
    residualGavity = gravityVector - gravityVectorAfter
    
    residualGavity = sp.array([residualGavity.x, residualGavity.y, residualGavity.z])
    
    return sp.sqrt(sp.dot(residualGavity, residualGavity))

def objectiveFunction(parameters, dataSet, acceleroMisalignmentsAndScales, acceleroBias):
    
    
    residuals = []
    
    for motion, statisticsByLabelBeforeMotion, samplesByLabelInMotion, statisticsByLabelAfterMotion in dataSet :
        
        residuals.append(residual(parameters, motion, statisticsByLabelBeforeMotion, samplesByLabelInMotion, statisticsByLabelAfterMotion, acceleroMisalignmentsAndScales, acceleroBias))
   
    print sp.dot(residuals, residuals)
    
    return sp.dot(residuals, residuals)


def fit(dataSet, acceleroMisalignmentsAndScales, acceleroBias):
    
    idg1215range = math.radians(67.0)/((2.8/3.3) * 512.0) * 1.5
    lisy300range = math.radians(300.0)/512.0
    
    misalignmentsAndScalesPriors = sp.array([idg1215range, 0, 0,
                                             0, idg1215range, 0,
                                             0, 0, lisy300range])

    deltaIDG1215range = 0.15 * idg1215range
    
    deltaLISY300range = 0.15 * lisy300range
    
    crossAxisRanges = (- 0.05 * idg1215range, 0.05 * idg1215range)
    
    ranges = [(idg1215range - deltaIDG1215range, idg1215range + deltaIDG1215range), crossAxisRanges, crossAxisRanges, 
              crossAxisRanges, (idg1215range - deltaIDG1215range, idg1215range + deltaIDG1215range), crossAxisRanges,
              crossAxisRanges, crossAxisRanges, (lisy300range - deltaLISY300range, lisy300range + deltaLISY300range)]
    
    
#    parameters, f, d = optimize.fmin_l_bfgs_b(func = objectiveFunction, x0 = sp.reshape(misalignmentsAndScalesPriors, 9), bounds = ranges, args = (dataSet, acceleroMisalignmentsAndScales, acceleroBias), approx_grad = True)
    parameters, f, d = optimize.fmin_l_bfgs_b(func = objectiveFunction, x0 = sp.ones(9), args = (dataSet, acceleroMisalignmentsAndScales, acceleroBias), approx_grad = True)
    
    
    return sp.reshape(parameters, (3, 3))


    
