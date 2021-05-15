'''
Created on 2009-11-23

@author: malem303
'''
import unittest

import scipy as sp

from imugrabber.algorithms import scipy_utils

from numpy import testing

from cgkit import cgtypes

class RotationTests(unittest.TestCase):


    def setUp(self):
        
        self.YPRAngles = (sp.pi / 5, sp.pi / 6, sp.pi / 7)
        
        self.unitVecAlongZ = sp.array([0.0,0.0,1.0])
        
        self.unitVecAlongY = sp.array([0.0,1.0,0.0])
        
        self.unitVecAlongX = sp.array([1.0,0.0,0.0])
        
        self.vecXYZ = sp.array([1.0,1.0,1.0])
        
    def testbuild_x_scipy_utils_matrix(self):
        
        testing.assert_equal(scipy_utils.roll_transform(0.0), sp.identity(3))
        
        testing.assert_almost_equal(scipy_utils.roll_transform(sp.pi / 4), 
                                    sp.array([  [ 1.        ,  0.        ,  0.        ],
                                                [ 0.        ,  0.70710678,  0.70710678],
                                                [ 0.        , -0.70710678,  0.70710678]]))
        
        vec = sp.dot(scipy_utils.roll_transform(sp.pi / 2), self.unitVecAlongZ)
        
        testing.assert_almost_equal(vec, self.unitVecAlongY)
        
        
        pass

    def testYPR_to_directionCosineMatrix(self):
        
        testing.assert_equal(scipy_utils.YPR_matrix(0.0, 0.0, 0.0), sp.identity(3))
        
        
        dcm = scipy_utils.YPR_matrix(*self.YPRAngles)
        
        testing.assert_almost_equal(dcm, sp.array([[ 0.78026193,  0.37575434, -0.5       ],
                                                   [-0.08623121,  0.85641436,  0.50903696],
                                                   [ 0.61948003, -0.35406655,  0.70062927]]))
        
        vec = sp.dot(dcm, self.vecXYZ)
        
        testing.assert_almost_equal(vec, sp.array([ 0.65601627,  1.27922011,  0.96604274]))
        
        vec = sp.dot(scipy_utils.YPR_matrix(sp.pi/2, 0.0, 0.0), self.unitVecAlongZ)
        
        testing.assert_almost_equal(vec, self.unitVecAlongY)
        
        vec = sp.dot(scipy_utils.YPR_matrix(sp.pi/2, 0.0, sp.pi/2), self.unitVecAlongX)
        
        testing.assert_almost_equal(vec, self.unitVecAlongZ)
        
        pass
    
    def testquaternion_to_directionCosineMatrix(self):
        
        quat = scipy_utils.to_quaternion(*self.YPRAngles)
        
        dcm = scipy_utils.quaternion_to_YPR_matrix(quat)
        
        testing.assert_almost_equal(dcm, sp.array([[ 0.78026193,  0.37575434, -0.5       ],
                                                   [-0.08623121,  0.85641436,  0.50903696],
                                                   [ 0.61948003, -0.35406655,  0.70062927]]))
        
    def testto_quaternion_to_YPR(self):
        
        quat = scipy_utils.to_quaternion(*self.YPRAngles)
        
        testing.assert_almost_equal(quat, sp.array([ 0.91341469,  0.23622992,  0.30639972,  0.12644464]))
        
        YPR = scipy_utils.to_YPR(quat) 
        
        testing.assert_almost_equal(sp.array(YPR), sp.array(self.YPRAngles))
        
        dcmQuat = scipy_utils.quaternion_to_YPR_matrix(quat)
        
        testing.assert_almost_equal(dcmQuat, scipy_utils.YPR_matrix(*self.YPRAngles))
        
    def testquaternion_product(self):
        
        quat = scipy_utils.to_quaternion(*self.YPRAngles)
        dcm = scipy_utils.YPR_matrix(*self.YPRAngles)
        
        quat2 = scipy_utils.quaternion_product(quat, quat)
        
        
        testing.assert_almost_equal(scipy_utils.quaternion_to_YPR_matrix(quat2), sp.dot(dcm, dcm))
        
        
    def testquaternion_derivative(self):
        
        quat = scipy_utils.to_quaternion(*self.YPRAngles)
        
        print scipy_utils.quaternion_norm(quat)
        
        d_quat = scipy_utils.quaternion_derivative(2*sp.pi, 0.0, 0.0, quat)
        
        print scipy_utils.quaternion_norm(d_quat)
        
        quat_1s_later = quat + 0.01 * d_quat
        
        cgquat = cgtypes.quat(quat_1s_later)
        
        print cgquat
        
        print cgquat.normalize()
        

        
        quat_1s_later = quat_1s_later / sp.sqrt(scipy_utils.quaternion_norm(quat_1s_later))
        
        print quat_1s_later
        
        print scipy_utils.quaternion_norm(quat_1s_later)
        
        roll, pitch, yaw  = scipy_utils.to_YPR(quat_1s_later)
        
        testing.assert_almost_equal(roll, self.YPRAngles[0] + .01)
        
    def testDavailus(self):
        
        q_w = cgtypes.quat(0.0, 2*sp.pi, 0.0, 0.0)
        
        d_t = 1.0
        
        q_w = q_w * d_t * 0.5
        
        e_dav = q_w.exp()
        
        quat_t0 = cgtypes.quat(scipy_utils.to_quaternion(*self.YPRAngles))
        
        quat_t1 = quat_t0 * e_dav
        
        roll, pitch, yaw  = scipy_utils.to_YPR((quat_t1.w, quat_t1.x, quat_t1.y, quat_t1.z))
        
        testing.assert_almost_equal(roll, self.YPRAngles[0])
        
        

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()