'''
Created on 2009-12-04

@author: malem303
'''
import unittest

import BugScene
from cgkit.all import *
import math

class BugSceneTest(unittest.TestCase):

    def testaccelerometerReading(self):
        
        self.bug = BugScene.BugScene()
        
        
        self.assertAlmostEquals(self.bug.gVectorInTableBCoords(), vec4([0, 0, -1, 0]))
        
        self.bug.rotativeTableAAngle = math.pi/2
        
        
        self.assertAlmostEquals(self.bug.gVectorInTableBCoords(), vec4([0, 1, 0, 0]))
        
        self.bug.rotativeTableAAngle = 0
        
                
        self.assertAlmostEquals(self.bug.gVectorInTableBCoords(), vec4([0, 0, -1, 0]))
                
        self.bug.rotativeTableBAngle = math.pi/2
        
        
        self.assertAlmostEquals(self.bug.gVectorInTableBCoords(), vec4([-1, 0, 0, 0]))
        
        self.bug.rotativeTableBAngle = 0
        
        
        self.assertAlmostEquals(self.bug.gVectorInTableBCoords(), vec4([0, 0, -1, 0]))
        
        self.bug.baseRotationMat3 = mat3.fromEulerXYZ(math.pi/2, 0.0, 0.0)
        
                
        self.assertAlmostEquals(self.bug.gVectorInTableBCoords(), vec4([0, 1, 0, 0]))


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()