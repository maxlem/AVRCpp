'''
Created on 2010-02-24

@author: malem303
'''
import math
import scipy as sp
from scipy import interpolate
from imugrabber.algorithms import fong_accelero, fong_gyro, regression_accelero, regression_gyro, slave_model_filter, utils
from imugrabber.algorithms import io
from imugrabber.experiments import plots

import matplotlib.pyplot as plt

_timescale = (64.0/16.0e6)
_maxTimestamp = 65535
    
def fit_accelero_parameters_fong():
    
    dataSet = io.float_columns_from_CSV(columnsMask = ('longitude', 'latitude', 'avgX','avgY', 'avgZ'))
    measures = utils.build_measures_matrix(dataSet['avgX'], dataSet['avgY'], dataSet['avgZ'])
    misalignmentsAndScales, biases  = fong_accelero.fit(measures)
    
    longitudes, latitudes =  dataSet["longitude"], dataSet["latitude"]
    correctedMesaures = utils.correct_measures(misalignmentsAndScales, biases, measures)
    residuals = fong_accelero.residuals(utils.concatenate(misalignmentsAndScales, biases), measures)
    
    return misalignmentsAndScales, biases, residuals, correctedMesaures, longitudes, latitudes



def fit_accelero_parameters_regression():
    
    dataSet = io.float_columns_from_CSV(columnsMask = ('longitude', 'latitude', 'avgX','avgY', 'avgZ'))
    measures = utils.build_measures_matrix(dataSet['avgX'], dataSet['avgY'], dataSet['avgZ'])
    longitudes, latitudes =  dataSet["longitude"], dataSet["latitude"]
    targets = utils.build_targets_matrix(longitudes, latitudes)
    misalignmentsAndScales, biases  = regression_accelero.fit(targets, measures)
    
    io.serialize_results((misalignmentsAndScales, biases), io._pkl_path, "accelero_params_%s.pkl")
    
    correctedMesaures = utils.correct_measures(misalignmentsAndScales, biases, measures)
    residuals = regression_accelero.residuals(utils.concatenate(misalignmentsAndScales, biases), targets, measures)
    
#    plots.plot_residuals(residuals, longitudes, latitudes)
    plots.plot_fit(correctedMesaures, longitudes, latitudes)
    plots.show_figures()
    



def fit_gyro_parameters_fong():

    acceleroDataSet = io.float_columns_from_CSV(columnsMask = ('longitude', 'latitude', 'avgX','avgY', 'avgZ'))
    measures = utils.build_measures_matrix(acceleroDataSet['avgX'], acceleroDataSet['avgY'], acceleroDataSet['avgZ'])
    acceleroMisalignmentsAndScales, acceleroBiases  = fong_accelero.fit(measures)
    
    gyroDataSet = prepareGyroDatatSet()
    
    misalignmentsAndScales = fong_gyro.fit(gyroDataSet, acceleroMisalignmentsAndScales, acceleroBiases)
    
#    io.serialize_results(misalignmentsAndScales, io._pkl_path, "gyro_params_%s.pkl")
    
    plotGyroFits(gyroDataSet, misalignmentsAndScales)
    

def fit_gyro_parameters_regression():

    gyroDataSet = prepareGyroDatatSet()
    
    targetKnots = utils.extract_targets_from_hal_logs_abvt()
    
    misalignmentsAndScales, skew, shift = regression_gyro.fit(targetKnots, gyroDataSet)
#    
    io.serialize_results((misalignmentsAndScales, skew, shift), io._pkl_path, "gyro_params_%s.pkl")
    
    misalignmentsAndScales, skew, shift = io.deserialize_results(io._pkl_path, "gyro_params_latest.pkl")
    
    plotGyroFits(gyroDataSet, misalignmentsAndScales, skew, shift, targetKnots)
    

def fit_filter_parameters():

    statisticsByLabelBeforeMotion, samplesByLabelInMotion = io.deserialize_results()
    
    misalignmentsAndScales, skew, shift = io.deserialize_results(io._pkl_path, "gyro_params_latest.pkl")
    gyroMeasures = utils.extract_and_correct_gyro_motion(misalignmentsAndScales, statisticsByLabelBeforeMotion, samplesByLabelInMotion)
    
    
    misalignmentsAndScales, biases = io.deserialize_results(io._pkl_path, "accelero_params_latest.pkl")
    accMeasures = utils.extract_and_correct_accelero_motion(misalignmentsAndScales, biases, samplesByLabelInMotion)
    
    measures = sp.r_[accMeasures, gyroMeasures]
    
     
    utils.rescale_gyro_motion_timestamps(samplesByLabelInMotion, _timescale)
    imuTimestamps = samplesByLabelInMotion['timestamps']
    timestamps = sp.array(imuTimestamps) * skew
    timestamps += sp.ones_like(timestamps) * shift
    
    (xSplineTCK, ySplineTCK, zSplineTCK, aSplineTCK, bSplineTCK) = utils.extract_targets_from_hal_logs_xyzabvt()
   
    x = sp.r_[interpolate.splev(timestamps, xSplineTCK, der = 0)]
        
    y = sp.r_[interpolate.splev(timestamps, ySplineTCK, der = 0)]
        
    z = sp.r_[interpolate.splev(timestamps, zSplineTCK, der = 0)]
    
    a = sp.r_[interpolate.splev(timestamps, aSplineTCK, der = 0)]
    
    b = sp.r_[interpolate.splev(timestamps, bSplineTCK, der = 0)]
    
    trg = sp.r_['0,2',x,y,z,a,b]
    
    plots.plot_encoders(trg, timestamps)
    plots.show_figures()
    
    filterParams = slave_model_filter.fit(sp.r_['0,2',x,y,z,a,b], measures, timestamps)
#    
    io.serialize_results(filterParams, io._pkl_path, "filter_params_%s.pkl")
    
def prepareGyroDatatSet():
    
    (statisticsByLabelBeforeMotion, samplesByLabelInMotion) = io.deserialize_results()
    
    utils.rescale_gyro_motion_timestamps(samplesByLabelInMotion, _timescale)

    
    utils.smooth_gyro_motion(samplesByLabelInMotion)
    
#    gyroDataSet = utils.slice_gyro_dataSet(gyroDataSet, 0, 225)

    return (statisticsByLabelBeforeMotion, samplesByLabelInMotion)

def plotGyroFits(gyroDataSet, misalignmentsAndScales, skew, shift, targetKnots = None):
    
    figureNumber = 0
    statisticsByLabelBeforeMotion, samplesByLabelInMotion = gyroDataSet
    correctedMeasures = utils.extract_and_correct_gyro_motion(misalignmentsAndScales, statisticsByLabelBeforeMotion, samplesByLabelInMotion)
    timestamps = sp.array(gyroDataSet[1]['timestamps']) * skew
    timestamps += sp.ones_like(timestamps) * shift
    
    
    if targetKnots is not None :
        plots.plot_targets(regression_gyro.computeTargetVelocities(targetKnots, timestamps),
                           timestamps, 
                           figureNumber,
                           (timestamps[0], timestamps[-1]),
                           math.pi)
        
    plots.plot_motion(correctedMeasures, 
                      timestamps, 
                      "Gyro measurements vs CNC targets", 
                      figureNumber, 
                      (timestamps[0], timestamps[-1]),
                      math.pi)

    
    figureNumber += 1

    plots.show_figures()

    