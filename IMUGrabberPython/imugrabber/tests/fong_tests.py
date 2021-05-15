'''
Created on 2009-08-11

@author: malem303
'''
import unittest

from imugrabber.algorithms import fong_accelero, utils, statistics
from imugrabber.algorithms import io
import os

import scipy as sp
from numpy import testing

class FongTests(unittest.TestCase):

    def setUp(self):
        
        self.misalignmentsAndScales = sp.array([[  4.08269136e-03,  -1.96002082e-05,   1.16692771e-04],
                                                 [ -6.73123099e-06,   3.86658837e-03,  -2.77361987e-04],
                                                 [ -6.43895175e-05,   2.91260930e-04,  3.93614477e-03]])
        self.biases = sp.array([[ 604.00283039],
                             [ 480.33539568],
                             [ 522.23054001]])
        
    def test_fit_parameters(self):
        
        dataSet = io.float_columns_from_CSV(csvFileName = "FongTests.csv", path = io._test_path)
        
        x, y, z = dataSet['avgX'], dataSet['avgY'], dataSet['avgZ']
        
        measures = utils.build_measures_matrix(x, y, z)
        
        misalignmentsAndScales, biases  = fong_accelero.fit(measures)
        
        testing.assert_almost_equal(misalignmentsAndScales, self.misalignmentsAndScales)
        
        testing.assert_almost_equal(biases, self.biases)

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()