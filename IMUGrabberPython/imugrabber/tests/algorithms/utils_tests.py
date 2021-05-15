'''
Created on 2010-03-31

@author: malem303
'''
import unittest

from imugrabber.algorithms import utils
import scipy as sp
import math
from numpy import testing

class utils_tests(unittest.TestCase):


    def testtransform_CNC_target(self):
        
        tx = 1.0
        ty = 5.0
        tz = -10.0
        
        a, b = -math.pi/2, 0
        testing.assert_almost_equal(
                                    utils.transform_CNC_target(0, 0, 0, a, b, tx, ty, tz),
                                    sp.array([tx, tz, -ty])
                                    )
        
        a, b = 0, -math.pi/2
        testing.assert_almost_equal(
                            utils.transform_CNC_target(0, 0, 0, a, b, tx, ty, tz),
                            sp.array([0, ty, tz + tx])
                            )
        
        a, b = -math.pi/2, -math.pi/2
        testing.assert_almost_equal(
                    utils.transform_CNC_target(0, 0, 0, a, b, tx, ty, tz),
                    sp.array([0, tz + tx, -ty])
                    )


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()