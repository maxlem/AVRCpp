'''
Created on 2010-02-08

@author: malem303
'''

from imugrabber.view import View
from imugrabber.experiments import ExperimentSceneMock

import unittest
from imugrabber.algorithms import regression_accelero
import scipy as sp
from scipy import linalg
from imugrabber.algorithms import statistics
from numpy import testing

class RegressionMethodTest(unittest.TestCase):

    
    
    def mockTrainingData(self):
        
        xRotations, yRotations = statistics.frange(-1.5, 1.0, 5), statistics.frange(-1.5, 1.0, 5)
        targets = []
        measures = []
        for xRotation in xRotations :
            for yRotation in yRotations :
                self.exp.rotativeTableAAngle = xRotation
                self.exp.rotativeTableBAngle = yRotation
                
                gravityVector = self.exp.gravityVector_IMU_coords()
                
                
                targets.append(gravityVector)
                
                measures.append(sp.dot(linalg.inv(self.misalignmentsAndScales), gravityVector) + self.biases)
        
        return targets, measures



        
         
    def testfitParameters(self):
        
        self.exp = ExperimentSceneMock.ExperimentSceneMock()
        self.misalignmentsAndScales = sp.array([[1.1,.1,-.3],[-.1,1.1,.2],[.3,-.2,1.1]])
        self.biases = sp.array([.1, .2, .3])
        
        targets, measures = self.mockTrainingData();
        
        misalignmentsAndScales, biases  = regression_accelero.fit(sp.transpose(sp.array(targets)), sp.transpose(sp.array(measures)))
        
        testing.assert_almost_equal(misalignmentsAndScales, self.misalignmentsAndScales)
        
        testing.assert_almost_equal(biases, sp.reshape(self.biases,(3,1)))
        
        

        
        
        


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()