'''
Created on 2010-01-20

@author: malem303
'''
import scipy as sp
from numpy import testing
from imugrabber.algorithms import cgkit_to_scipy

def assert_almost_equal(actual, desired, decimal=7, err_msg='', verbose=True):
    
    
    return testing.assert_array_almost_equal(cgkit_to_scipy.convert(actual), cgkit_to_scipy.convert(desired), decimal, err_msg, verbose)