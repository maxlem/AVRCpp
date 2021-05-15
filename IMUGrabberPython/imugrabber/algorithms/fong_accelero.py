'''
Created on 2009-08-11

@author: malem303
'''

import scipy as sp
from scipy import optimize
from imugrabber.algorithms import utils


def residuals(modelParameters, measures):
    
    
    misalignmentsAndScales, biases = utils.unpack_parameters(modelParameters)
    
    correctedMesures = utils.correct_measures(misalignmentsAndScales, biases, measures)
    
    correctedMesuresSquared = correctedMesures**2
    
    norms = sp.sqrt(correctedMesuresSquared[0,:] + correctedMesuresSquared[1,:] + correctedMesuresSquared[2,:]) 
    
    return sp.ones_like(norms) - norms

def fit(measures =  sp.c_[(1,2,3)*3]):
    
    biases, misalignmentsAndScales = utils.find_priors(measures)
    
    parameters, flags = optimize.leastsq(residuals, utils.concatenate(misalignmentsAndScales, biases), args = measures, warning = False)
    
    return utils.unpack_parameters(parameters)
    
