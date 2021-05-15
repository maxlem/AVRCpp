'''
Created on 2010-02-18

@author: malem303
'''

import scipy as sp
from scipy import interpolate
import math
from imugrabber.algorithms import io
#from cgkit import cgtypes
from imugrabber.algorithms import scipy_utils
import matplotlib.pyplot as plt



def extract_targets_from_hal_logs_abvt(shiftToZero = True):
    
        
    targetsMatrix = sp.array(io.parse_halscope_log_abvt("halscope_single_dataset.txt"))
    
    (rowCount, colCount) = targetsMatrix.shape
    
    
    aTargets, bTargets, velocites, targetTimestamps = targetsMatrix[:,0], targetsMatrix[:,1], targetsMatrix[:,2], targetsMatrix[:,3]
    
    if(shiftToZero):
        targetTimestamps -= sp.ones_like(targetTimestamps) * min(targetTimestamps)
    
    aSplineTCK = interpolate.splrep(targetTimestamps, sp.radians(smooth(aTargets)))
    bSplineTCK = interpolate.splrep(targetTimestamps, sp.radians(smooth(bTargets)))
    
    print "B = %f, E = %f, len = %d" % (min(targetTimestamps), max(targetTimestamps), len(targetTimestamps))                   
        
#        plt.plot(targetTimestamps, interpolate.splev(targetTimestamps, aSplineTCK, der = 1))
#        plt.show()
    
    return (aSplineTCK, bSplineTCK)
        
def extract_targets_from_hal_logs_xyzabvt(shiftToZero = True):
    
        
    targetsMatrix = sp.array(io.parse_halscope_log_xyzabvt("halscope_xyzabvt_dataset.txt"))
    
    (rowCount, colCount) = targetsMatrix.shape
    
    
    xTargets, yTargets, zTargets, aTargets, bTargets, velocites, targetTimestamps = targetsMatrix[:,0], targetsMatrix[:,1], targetsMatrix[:,2], targetsMatrix[:,3], targetsMatrix[:,4], targetsMatrix[:,5], targetsMatrix[:,6]
    
    if(shiftToZero):
        targetTimestamps -= sp.ones_like(targetTimestamps) * min(targetTimestamps)
   
    xSplineTCK = interpolate.splrep(targetTimestamps, sp.radians(xTargets))
    ySplineTCK = interpolate.splrep(targetTimestamps, sp.radians(yTargets))
    zSplineTCK = interpolate.splrep(targetTimestamps, sp.radians(zTargets)) 
    aSplineTCK = interpolate.splrep(targetTimestamps, sp.radians(aTargets))
    bSplineTCK = interpolate.splrep(targetTimestamps, sp.radians(bTargets))
    
    print "B = %f, E = %f, len = %d" % (min(targetTimestamps), max(targetTimestamps), len(targetTimestamps))                   
        
#        plt.plot(targetTimestamps, interpolate.splev(targetTimestamps, aSplineTCK, der = 1))
#        plt.show()
    
    return (xSplineTCK, ySplineTCK, zSplineTCK, aSplineTCK, bSplineTCK)
            
def addTimestamps(samplesByLabel, timescale, shiftToZero = True):

        
    timestamps = sp.array(samplesByLabel['s'], dtype=sp.double) * timescale
    
    if(shiftToZero):
        timestamps -= sp.ones_like(timestamps) * min(timestamps)
            
    samplesByLabel['timestamps'] = list(timestamps)

def computeTimespan(sampleByLabel):
    return max(sampleByLabel['timestamps']) - min(sampleByLabel['timestamps'])

def rescale_gyro_motion_timestamps(samplesByLabelInMotion,  timescale):
    
    addTimestamps(samplesByLabelInMotion, timescale)

    print "B = %f, E = %f, len = %d" % (min(samplesByLabelInMotion['timestamps']), max(samplesByLabelInMotion['timestamps']), len(samplesByLabelInMotion['timestamps']))                   

#        plt.figure(index)
#        plt.plot(samplesByLabelInMotion['timestamps'], samplesByLabelInMotion['a'])
#    plt.show()
        
def smooth_gyro_motion(samplesByLabelInMotion, labels = "abc", convolutionWindowSize = 10):
    
    for label in list(labels) :
        smoothedArray = smooth(sp.array(samplesByLabelInMotion[label]), convolutionWindowSize)
        samplesByLabelInMotion[label] = list(smoothedArray)

def extract_and_correct_gyro_motion(misalignmentsAndScales, statisticsByLabelBeforeMotion, samplesByLabelInMotion):
    
    aBias, bBias, cBias = statisticsByLabelBeforeMotion['a'][0], statisticsByLabelBeforeMotion['b'][0], statisticsByLabelBeforeMotion['c'][0]
    aSamples, bSamples, cSamples = samplesByLabelInMotion['a'], samplesByLabelInMotion['b'], samplesByLabelInMotion['c']
    
    measures = build_measures_matrix(aSamples, bSamples, cSamples)
    
    correctedMeasures = correct_measures(misalignmentsAndScales, sp.array([[aBias], [bBias], [cBias]]), measures)
    
    return correctedMeasures

def extract_and_correct_accelero_motion(misalignmentsAndScales, biases, samplesByLabelInMotion):
    
    measures = build_measures_matrix(samplesByLabelInMotion['x'], samplesByLabelInMotion['y'], samplesByLabelInMotion['z'])
    
    correctedMeasures = correct_measures(misalignmentsAndScales, biases, measures)
    
    return correctedMeasures

def gravityVector_IMU_coords(xRotation, yRotation):
    """
    First rotate the gravity vector (in NED frame) around x axis, then around y
    """
    return sp.dot(
                  scipy_utils.pitch_transform(yRotation), 
                  sp.dot(
                         scipy_utils.roll_transform(xRotation), 
                         sp.array([0, 0, -9.81])
                         )
                  )


def transform_CNC_target(x, y, z, a, b, tx, ty, tz):
    
    position = sp.array([x,y,z])
    
    position += sp.dot(
                       scipy_utils.roll_transform(-a), 
                       sp.array([0, ty, tz]) + 
                       sp.dot(
                              scipy_utils.pitch_transform(-b), 
                              sp.array([tx,0 ,0])
                              )
                       )
    
    return position
    
    

def build_targets_matrix(xRotations, yRotations):
    
    gravityVectors = []
    for index in range(len(xRotations)) :
        gravityVector = gravityVector_IMU_coords(math.radians(xRotations[index]), math.radians(yRotations[index]))
        gravityVectors.append(gravityVector)
        
    return sp.transpose(sp.array(gravityVectors))

def build_measures_matrix(x, y, z):
    x = sp.r_[x]
    y = sp.r_[y]
    z = sp.r_[z]
    return sp.r_['0,2', x, y, z]

def concatenate(misalignmentsAndScales, biases):
    
    if sp.ndim(biases) > 1 :
        biases = sp.reshape(biases, 3)
        
    modelParametersMatrix = sp.concatenate((misalignmentsAndScales, sp.expand_dims(biases, axis=1)), axis=1)
    
    return sp.reshape(modelParametersMatrix, 12)

def unpack_parameters(parameters):
    parametersMatrix = sp.reshape(parameters, (3, 4))
    misalignmentsAndScales = parametersMatrix[:, :3]
    biases = parametersMatrix[:, 3:4]
    
    return misalignmentsAndScales, biases

def smooth(x, window_len=10, window='hanning'):
    """smooth the data using a window with requested size.
    
    This method is based on the convolution of a scaled window with the signal.
    The signal is prepared by introducing reflected copies of the signal 
    (with the window size) in both ends so that transient parts are minimized
    in the begining and end part of the output signal.
    
    input:
        x: the input signal 
        window_len: the dimension of the smoothing window
        window: the type of window from 'flat', 'hanning', 'hamming', 'bartlett', 'blackman'
            flat window will produce a moving average smoothing.

    output:
        the smoothed signal
        
    example:

    import numpy as np    
    t = np.linspace(-2,2,0.1)
    x = np.sin(t)+np.random.randn(len(t))*0.1
    y = smooth(x)
    
    see also: 
    
    numpy.hanning, numpy.hamming, numpy.bartlett, numpy.blackman, numpy.convolve
    scipy.signal.lfilter
 
    TODO: the window parameter could be the window itself if an array instead of a string   
    TAKEN FROM scipy cookbook
    """

    if x.ndim != 1:
        raise ValueError, "smooth only accepts 1 dimension arrays."

    if x.size < window_len:
        raise ValueError, "Input vector needs to be bigger than window size."

    if window_len < 3:
        return x

    if not window in ['flat', 'hanning', 'hamming', 'bartlett', 'blackman']:
        raise ValueError, "Window is on of 'flat', 'hanning', 'hamming', 'bartlett', 'blackman'"

    s=sp.r_[2*x[0]-x[window_len:1:-1], x, 2*x[-1]-x[-1:-window_len:-1]]
    #print(len(s))
    
    if window == 'flat': #moving average
        w = sp.ones(window_len,'d')
    else:
        w = getattr(sp, window)(window_len)
    y = sp.convolve(w/w.sum(), s, mode='same')
    return y[window_len-1:-window_len+1]

def correct_measures(misalignmentsAndScales, biases, measures):
    
    rows, cols = measures.shape
    
    biasesMaxtrix = sp.repeat(biases, cols, axis = 1)
    
    return sp.dot(misalignmentsAndScales, measures - biasesMaxtrix)

def correct_measure(misalignmentsAndScales, biases, measure):
    
    return sp.dot(misalignmentsAndScales, sp.array(measure) - sp.array(biases))

def find_acceleromoeter_scale_bias_priors(measures):
    maxZ = sp.amax(measures)
    minZ = sp.amin(measures)
    bias = minZ + (maxZ - minZ) / 2.0
    scale = 1/(maxZ - bias)
    
    return scale, bias

def find_priors(measures):
    scale, bias = find_acceleromoeter_scale_bias_priors(measures)
    misalignmentsAndScales = sp.identity(3) * scale
    biases = sp.ones(3) * bias
    return biases, misalignmentsAndScales


