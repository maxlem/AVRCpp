'''
Created on 2009-07-27

@author: malem-cnc
'''
import unittest
from imugrabber.algorithms import statistics
from imugrabber.tests.mocks import mocks
from numarray import mlab
import scipy as sp

class Statistics(unittest.TestCase):

    def setUp(self):
        
        self.samples = statistics.frange(5.0,15.0, 10)
        self.samplesByLabels = mocks.samplesByLabels()



    def tearDown(self):
        pass


    def test_avg_std(self):
        statisticsByLabel = statistics.samplesMeanStandardDeviation(self.samplesByLabels)
        
        (mean, std) = statisticsByLabel['x']
        self.assertAlmostEquals(mean, 10.0)
        self.assertAlmostEquals(std, 3.1914236925211266)
        
        (mean, std) = statisticsByLabel['y']
        self.assertAlmostEquals(mean, 5.0)
        self.assertAlmostEquals(std, 3.191423692521127)
        
    def test_normalize_against_z(self):
        x, y, z = statistics.normalize_against_z((sp.r_[self.samples] * 0.999999999).tolist(), (sp.r_[self.samples] * 1.00000001).tolist(), self.samples)
        
        self.assertAlmostEquals(sp.mean(x),0.0)
        self.assertAlmostEquals(sp.mean(y),0.0)
        self.assertAlmostEquals(sp.mean(z),0.0)


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()