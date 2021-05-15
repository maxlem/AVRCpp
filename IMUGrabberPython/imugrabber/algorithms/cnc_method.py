'''
Created on 2010-02-08

@author: malem303
'''


from scipy import *
from cgkit import cgtypes
from scipy.optimize import leastsq
from numpy.dual import norm


def residuals(parameters, predictions, inputs, experimentScene):
    
    residuals = []
    
    experimentScene.imuXYZAngles = (parameters[0], parameters[1], parameters[2])
    
    for i in range(len(predictions)):
        
        xRotation, yRotation = inputs[i]
        
        experimentScene.rotativeTableAAngle = xRotation
        experimentScene.rotativeTableBAngle = yRotation
        
        
        difference = cgtypes.vec3(predictions[i]) - experimentScene.gravityVector_IMU_coords()
        residuals.append(difference.length())

    
    return residuals
    
    
def fit(gravityVectors, xyRotations, experimentScene):
    parameters, flag = leastsq(residuals, ones(3), args=(gravityVectors, xyRotations, experimentScene))
    
    meanSquares = residuals(parameters, gravityVectors, xyRotations, experimentScene)
    
    return parameters, dot(meanSquares,meanSquares)

        