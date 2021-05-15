'''
Created on 2010-02-17

@author: malem303
'''
import scipy as sp
import math

from scipy.optimize import leastsq
from imugrabber.algorithms import utils




def residuals(parameters, targets, measures):
    

    misalignmentsAndScales, biases = utils.unpack_parameters(parameters)
    
    predictions = utils.correct_measures(misalignmentsAndScales, biases, measures)
    
    differences = (targets - predictions)**2
    
    residuals = sp.sqrt(differences[0,:] + differences[1,:] + differences[2,:])
    
    print sp.dot(residuals, residuals)
    
    return residuals 
    
    



def fit(targets, measures):
    
    biases, misalignmentsAndScales = utils.find_priors(measures)
    
    
    parameters, flag = leastsq(residuals, utils.concatenate(misalignmentsAndScales, biases), args=(targets, measures), maxfev = 100000)
    
    return utils.unpack_parameters(parameters)