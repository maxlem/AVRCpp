'''
Created on 2010-01-18

@author: malem303
'''
import unittest
from imugrabber.filtering.SimpleDynamicsFilter import SimpleDynamicsFilter
from numpy import testing
import scipy as sp
from imugrabber.algorithms import scipy_utils
from cgkit.cgtypes import *
import cgkit_testing
import math

class SimpleDynamicsFilterTest(unittest.TestCase):


    def setUp(self):
        pass


    def tearDown(self):
        pass


    def testLinearMovement(self):
        
#        csvFile = open("../../results/tests/sdf.csv", "r")
#        reader = csv.reader(csvFile, delimiter=',', quotechar='"')
#        
#        labels = reader.next()
#        
#        input = sp.zeros((0,len(labels)))
#        for row in reader:
#            input.resize((reader.line_num-1,len(labels)))
#            input[reader.line_num-2] = sp.array(row)
#        
#        csvFile.close()
        
        sdf = SimpleDynamicsFilter()

        cgkit_testing.assert_almost_equal(sdf.velocityBody, vec3([0.0, 0.0, 0.0]))
                
        cgkit_testing.assert_almost_equal(sdf.positionNED, vec3([0.0, 0.0, 0.0]))
        
        cgkit_testing.assert_almost_equal(sdf.orientationBody, quat(1))
        
        sdf.transition(vec3([1.0, 0.0, 1.0]), vec3([0.0, 0.0, 0.0]), sdf.timestamp + .1)
        
        cgkit_testing.assert_almost_equal(sdf.velocityBody, vec3([0.1, 0.0, 0.0]))
                        
        cgkit_testing.assert_almost_equal(sdf.positionNED, vec3([0.01, 0.0, 0.0]))
        
        cgkit_testing.assert_almost_equal(sdf.orientationBody, quat(1))
        
        sdf.transition(vec3([-1.0, 0.0, 1.0]), vec3([0.0, 0.0, 0.0]), sdf.timestamp + .1)
        
        cgkit_testing.assert_almost_equal(sdf.velocityBody, vec3([0.0, 0.0, 0.0]))
        
        cgkit_testing.assert_almost_equal(sdf.positionNED, vec3([0.01, 0.0, 0.0]))
        
        cgkit_testing.assert_almost_equal(sdf.orientationBody, quat(1))
    
    def testAngularMovement(self):
        
        angularVelocity = vec3([math.pi/2, 0, 0])
        
        sdf = SimpleDynamicsFilter()
        
        sdf.transition(sdf._predictLinearAccelerationFromGravityAndAngularVelocity(angularVelocity), angularVelocity, sdf.timestamp + .1)
        
        roll, pitch, yaw  = sdf.orientationBody.toMat3().toEulerZYX()
        
        self.assertAlmostEqual(roll, angularVelocity.x * 0.1)
        
        self.assertAlmostEqual(pitch, 0.0)
        
        self.assertAlmostEqual(yaw, 0.0)
        
        cgkit_testing.assert_almost_equal(sdf.velocityBody, vec3([0.0, -0.01564345,  0.00123117]))
        
        cgkit_testing.assert_almost_equal(sdf.positionNED, vec3([0.0, -0.00156434, -0.00012312]))
        
        sdf.transition(sdf._predictLinearAccelerationFromGravityAndAngularVelocity(-angularVelocity), -angularVelocity, sdf.timestamp + .1)
        
        roll, pitch, yaw  = sdf.orientationBody.toMat3().toEulerZYX()
        
        self.assertAlmostEqual(roll, 0.0)
        
        self.assertAlmostEqual(pitch, 0.0)
        
        self.assertAlmostEqual(yaw, 0.0)
        
        cgkit_testing.assert_almost_equal(sdf.velocityBody, vec3([0.0, 0.0, 0.0])) # the movement stopped
                
        cgkit_testing.assert_almost_equal(sdf.positionNED, vec3([0.0, -0.00156434, -0.00012312])) # so the position remains the same
        
        sdf.measure(vec3([.25, .25, .94]).normalize())
        
        
    def testMeasure(self):
        
        angularVelocityNoYaw = vec3([math.pi/2, 0, 0])
        
        sdf = SimpleDynamicsFilter()
        
        sdf.transition(sdf._predictLinearAccelerationFromGravityAndAngularVelocity(angularVelocityNoYaw), angularVelocityNoYaw, sdf.timestamp + .1)
        
        cgkit_testing.assert_almost_equal(sdf.orientationBody, quat([0.99691733, 0.0784591,  0.,  0.]))
        
        sdf.measure(sdf._predictMagnetoBody())
        
        cgkit_testing.assert_almost_equal(sdf.orientationBody, quat([0.99691733, 0.0784591,  0.,  0.]))
        
        sdf.transition(sdf._predictLinearAccelerationFromGravityAndAngularVelocity(-angularVelocityNoYaw), -angularVelocityNoYaw, sdf.timestamp + .1)
        
        cgkit_testing.assert_almost_equal(sdf.orientationBody, quat(1))
        
        angularVelocityYaw = vec3([0, 0, math.pi/4])
        
        sdf.transition(sdf._predictLinearAccelerationFromGravityAndAngularVelocity(angularVelocityYaw), angularVelocityYaw, sdf.timestamp + .1)
        
        rollBody, pitchBody, yawBody  = sdf.orientationBody.toMat3().toEulerZYX()
        
        self.assertAlmostEqual(rollBody, 0.0)
        
        self.assertAlmostEqual(pitchBody, 0.0)
        
        self.assertAlmostEqual(yawBody, angularVelocityYaw.z * 0.1)
        
        # we want a +.01 rad error
        
        rollNED, pitchNED, yawNED = -rollBody, -pitchBody, -yawBody + 0.01
        
        correctOrientationBody = quat()
        
        correctOrientationBody.fromMat(mat3.fromEulerXYZ(rollNED, pitchNED, yawNED)).conjugate()
        
        sdf.measure(correctOrientationBody.rotateVec(sdf._magneticField))
        
        correctRollBody, correctPitchBody, correctYawBody  = sdf.orientationBody.toMat3().toEulerZYX()
        
        self.assertAlmostEqual(correctYawBody, yawBody + 0.01)


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()