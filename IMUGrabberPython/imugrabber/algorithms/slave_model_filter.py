'''
Created on 2010-03-27

@author: malem303
'''
import scipy as sp
from scipy import optimize, interpolate, linalg
from imugrabber.algorithms import scipy_utils, utils
import time
import PyIMUFiltering

def residuals(parameters, targets, measures, timestamps):
    
    filter = PyIMUFiltering.Filter()
    
    
    index = 0
    
    start = time.time()
    
    for timestamp in timestamps :
        
        
        
        if(timestamp <= 5.0):
            index += 1
            continue
        
        
        filter.filter(timestamp, list(measures[:,index]))
        
        state = filter.stateMean()
        
        x, y, z = targets[0:3,index]
        a, b = targets[3:5, index]
        
        
        target = utils.transform_CNC_target(x, y, z, a, b, 1, 5, -10)
        
        onesNEDtarget = sp.dot(
                      scipy_utils.roll_transform(-a), 
                      sp.dot(
                             scipy_utils.pitch_transform(-b), 
                             sp.ones(3)
                             )
                      )
        
        onesNEDactual = sp.dot(scipy_utils.quaternion_to_YPR_matrix(state[3:7]), sp.ones(3))
        
        print targets[0:9,index]
        
        residual = linalg.norm(state[0:3] - target) + linalg.norm(onesNEDtarget - onesNEDactual)
        
        print "position error = %f, angular position error = %f" % (linalg.norm(state[0:3] - target), linalg.norm(onesNEDtarget - onesNEDactual))
    
        print "time elapsed : %f, timestamp = %f" % (time.time() - start, timestamp)
    
        index += 1 



def fit(targets, measures, timestamps):
    
    parameters = [0]
    ranges = [(-1e99, 1e99)]
    parameters, f, d = optimize.fmin_l_bfgs_b(func = residuals, x0 = parameters, bounds = ranges, args = (targets, measures, timestamps), approx_grad = True, maxfun = 50, epsilon = 1e-8)
    