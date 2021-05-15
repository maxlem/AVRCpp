'''
Created on 2009-08-17

@author: malem303
'''
import os
import unittest
from imugrabber.algorithms import io
from imugrabber.algorithms import utils
from imugrabber.tests.mocks import mocks
import matplotlib.pyplot as plt
import scipy as sp

_tests_path = os.path.join(io._results_path, "tests")

class IOTests(unittest.TestCase):


    def setUp(self):
        self.testExplorationCSVFileName = "testExplorationCSVFile.csv"
        self.dataSet = mocks.trainingDataSet()

    def tearDown(self):
        pass

    def _test_exploration_to_CSV(self):
        io.exploration_to_CSV(self.dataSet, _tests_path)
        csvDataSet = io.float_columns_from_CSV(io.LATEST_EXPLORATION_CSV_FILE_NAME, ('avgX','avgY', 'avgZ'), _tests_path)
        self.assertAlmostEqual(csvDataSet['avgX'][0], -0.5)
        self.assertAlmostEqual(csvDataSet['avgY'][4], -0.555555555556)
        
        
    def _test_exploration_from_CSV(self):
        csvDataSet = io.float_columns_from_CSV(self.testExplorationCSVFileName, ('avgX','avgY', 'avgZ', 'stdZ'), _tests_path)
        self.assertEqual(len(csvDataSet.keys()), 4)
        self.assertEqual(len(csvDataSet['avgX']), 1250)
        self.assertAlmostEqual(csvDataSet['avgX'][0], 542.290000)
        self.assertAlmostEqual(csvDataSet['avgX'][3], 503.140000)
        self.assertAlmostEqual(csvDataSet['avgY'][23], 404.050000)
        self.assertAlmostEqual(csvDataSet['avgZ'][253], 555.210000)
        
    def test_parse_hal_log(self):
        
#        dataset = io.parse_hal_log("test.log")
#        
#        print dataset
        
        statisticsByLabelBeforeMotion, samplesByLabelInMotion = io.deserialize_results()

        utils.rescale_gyro_motion_timestamps(samplesByLabelInMotion, (8.0/16e6))
        
        motions = utils.extract_targets_from_hal_logs_abvt()
        
#        tagetsMat = sp.array(targets)
#        
#        plt.figure(1, figsize = (8,10))
#        plt.subplot(311)
#        plt.plot(tagetsMat[:,2], tagetsMat[:,1])
#        plt.ylabel('axis a reading')
#        plt.xlabel('seconds')

        


if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()