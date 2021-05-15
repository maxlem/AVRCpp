'''
Created on 2009-12-04

@author: malem303
'''
import unittest

from imugrabber.view import View
from imugrabber.experiments import ExperimentSceneMock
from pyemc.core import Machine, ModelListener
from cgkit import cgtypes
from cgkit.all import *
import math

class ExperimentSceneMockTest(unittest.TestCase):

    def __init__(self, testName):
        unittest.TestCase.__init__(self, testName)
        self.box = Box(name='box1')
        self.box2 = Box(name='box2', parent=self.box)
        self.box3 = Box(name='box3', parent=self.box2)
        self.box4 = Box(name='box4', parent=self.box3)
         

    def setUp(self):
        pass


    def tearDown(self):
        getScene().clear()



    def setTransforms(self, _transform):
        self.box.transform = _transform
        self.box2.transform = _transform
        self.box3.transform = _transform
        self.box4.transform = _transform

    def testWorldTransform(self):
        

        
        translation = vec3(1,1,1)
        rotation = mat3.fromEulerXYZ(1,1,1)
        
        _transform = self.buildTransform(translation, rotation)
        

        
        self.setTransforms(_transform)
        
        self.assertTrue(self.box.worldtransform == _transform)
        self.assertTrue(self.box2.worldtransform == _transform * _transform)
        self.assertTrue(self.box3.worldtransform == _transform * _transform * _transform)
        self.assertTrue(self.box4.worldtransform == _transform * _transform * _transform * _transform)
           
        self.box.transform = mat4(1)
        
        self.assertTrue(self.box2.worldtransform == _transform)
        self.assertTrue(self.box3.worldtransform == _transform * _transform)
        
        self.box2.transform = mat4(1)
        
        self.assertTrue(self.box3.worldtransform == _transform)
        

    def buildTransform(self, translation, rotation):
        transform = mat4(1)
        transform.setMat3(rotation)
        transform.translate(translation)
        return transform

    def testgVectorInIMUCoords(self):
        
        self.exp = ExperimentSceneMock.ExperimentSceneMock()
        
        self.assertAlmostEquals(self.exp.gravityVector_IMU_coords(), cgtypes.vec3([0, 0, -1]))
        
        self.exp.rotativeTableAAngle = math.pi/2
        self.assertAlmostEquals(self.exp.gravityVector_IMU_coords(), cgtypes.vec3([0, -1, 0]))
        
        self.exp.rotativeTableAAngle = 0
        self.assertAlmostEquals(self.exp.gravityVector_IMU_coords(), cgtypes.vec3([0, 0, -1]))
        
        self.exp.rotativeTableBAngle = math.pi/2
        self.assertAlmostEquals(self.exp.gravityVector_IMU_coords(), cgtypes.vec3([1, 0, 0]))
        
        self.exp.rotativeTableBAngle = 0
        self.assertAlmostEquals(self.exp.gravityVector_IMU_coords(), cgtypes.vec3([0, 0, -1]))
        
        self.exp.rotativeTableAAngle = 1.5
        self.exp.rotativeTableBAngle = 1.8
        
        rotation = cgtypes.mat3.fromEulerXYZ(1.5, 1.8, 0).inverse()
        
        self.assertAlmostEquals(self.exp.gravityVector_IMU_coords(), rotation * cgtypes.vec3([0, 0, -1]))
        
        self.exp.baseXYZAngles = (math.pi/2, 0.0, 0.0)
        self.assertAlmostEquals(self.exp.gravityVector_IMU_coords(), cgtypes.vec3([0, -1, 0]))
        
        
    def _testVisually(self):
        self.exp = ExperimentSceneMock.ExperimentSceneMock()
        self.exp.rotativeTableAAngle = -.2
        self.exp.rotativeTableBAngle = .2
        self.exp.imuXYZAngles = (.0, .0, .0)
        self.view = View.View()
        while(self.view.running):
            self.view.refresh()
            


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()