'''
Created on 2009-07-22

@author: malem303
'''
import matplotlib.pyplot as plt
import os, datetime, shutil
import pickle
import csv
from imugrabber.algorithms import statistics

_BASE_DIR = "../../"
_RESULTS_DIR = "results"

_results_path = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__), _BASE_DIR)), _RESULTS_DIR)
_pkl_path = os.path.join(_results_path, "pkl")
_csv_path = os.path.join(_results_path, "csv")
_test_path = os.path.join(_results_path, "tests")
_halscope_path = os.path.join(_results_path, "halscope")
_plots_path = os.path.join(_results_path, "plots")

_timestamp = str(datetime.datetime.now()).replace(' ','.')


LATEST_RESULTS_FILE_NAME = "results_latest.csv"

LATEST_SAMPLES_BY_LABEL_CSV_FILE_NAME = "samplesByLabel_latest.csv"
LATEST_SAMPLES_BY_LABEL_PKL_FILE_NAME = "samplesByLabel_latest.pkl"

LATEST_EXPLORATION_CSV_FILE_NAME = "exploration_latest.csv"
LATEST_EXPLORATION_PKL_FILE_NAME = "exploration_latest.pkl"

LATEST_MAXIMA_CSV_FILE_NAME = "maxima_latest.csv"
LATEST_MAXIMA_PKL_FILE_NAME = "maxima_latest.pkl"

def serialize_results(results, path = _pkl_path, fileName = "results_%s.pkl"):
    resultsSerializationFileName = os.path.join(path, fileName % _timestamp)
    
    resultsSerialization = open(resultsSerializationFileName, "wb")
    pickle.dump(results, resultsSerialization)
    resultsSerialization.close()
    
    shutil.copy(resultsSerializationFileName, os.path.join(path, fileName % "latest"))
    
def deserialize_results(path = _pkl_path, fileName = "results_latest.pkl"):
    resultsSerialization = open(os.path.join(_pkl_path, fileName), "rb")
    results = pickle.load(resultsSerialization)
    resultsSerialization.close()
    
    return results 

def serialize_maxima(maxima):
    maximaSerializationFileName = os.path.join(_pkl_path, "maxima_%s.pkl" % _timestamp)
    
    maximaSerialization = open(maximaSerializationFileName, "wb")
    pickle.dump(maxima, maximaSerialization)
    maximaSerialization.close()
    
    shutil.copy(maximaSerializationFileName, os.path.join(_pkl_path, LATEST_MAXIMA_PKL_FILE_NAME))
    
    
    

def deserialize_maxima(pickleFileName = LATEST_MAXIMA_PKL_FILE_NAME):
    maximaSerialization = open(os.path.join(_pkl_path, pickleFileName), "rb")
    content = pickle.load(maximaSerialization)
    maximaSerialization.close()
    
    return content 

def serialize_exploration(dataSet):
    
    explorationSerializationFileName = os.path.join(_pkl_path, "exploration_%s.pkl" % _timestamp)
    
    explorationSerialization = open(explorationSerializationFileName, "wb")
    pickle.dump(dataSet, explorationSerialization)
    explorationSerialization.close()
    
    shutil.copy(explorationSerializationFileName, os.path.join(_pkl_path, LATEST_EXPLORATION_PKL_FILE_NAME))
    
    

def deserialize_exploration(pickleFileName = LATEST_EXPLORATION_PKL_FILE_NAME):
    
    explorationSerialization = open(os.path.join(_pkl_path, pickleFileName), "rb")
    content = pickle.load(explorationSerialization)
    explorationSerialization.close()
    
    return content
    
def maximum_to_CSV(maximum):
    
    (longitude, latitude), value = maximum
    return "%f; %f; %f;" % (longitude, latitude, value)
    
def exploration_to_CSV(trainingDataSet, path = _csv_path):
    
    explorationCSVFileName = os.path.join(path, "exploration_%s.csv" % _timestamp)
    
    explorationCSV = open(explorationCSVFileName, "w")
    
    csvWriter = csv.writer(explorationCSV)
    
    headers = ["longitude", "latitude"]
    
    aSamplesByLabel = trainingDataSet[trainingDataSet.keys()[0]]
    
    for samplingLabel in sorted(aSamplesByLabel.keys()) :
        headers.append("avg%s" % samplingLabel.upper())
        headers.append("std%s" % samplingLabel.upper())
        
    csvWriter.writerow(headers)
    
    dataRows = []
    
    for position in sorted(trainingDataSet.iterkeys()):
        
        statisticsByLabel = statistics.samplesMeanStandardDeviation(trainingDataSet[position])
        dataRow = list(position)

        for label in sorted(statisticsByLabel.keys()) :
            (mean, std) = statisticsByLabel[label]
            dataRow.extend([mean, std])
        
        dataRows.append(dataRow)
        
    csvWriter.writerows(dataRows)            
        
    explorationCSV.close()
    
    shutil.copy(explorationCSVFileName, os.path.join(path, LATEST_EXPLORATION_CSV_FILE_NAME))
    
    return dataRows

def samplesByLabel_toCSV(samplesByLabel, path = _csv_path):
    
    csvFileName = os.path.join(path, "samplesByLabel_%s.csv" % _timestamp)
    
    csvFile = open(csvFileName, "w")
    
    csvWriter = csv.writer(csvFile)
    
        
    for label, samples in samplesByLabel.iteritems():
        row = [label]
        row.extend(samples)
        csvWriter.writerow(row)
        
        
    csvFile.close()
    
    shutil.copy(csvFileName, os.path.join(path, LATEST_SAMPLES_BY_LABEL_CSV_FILE_NAME))
    
def float_columns_from_CSV(csvFileName = LATEST_EXPLORATION_CSV_FILE_NAME, columnsMask = ('avgX','avgY', 'avgZ'), path = _csv_path):
    csvFile = open(os.path.join(path, csvFileName), "r")
    dictReader = csv.DictReader(csvFile)
    
    dataSet = dict.fromkeys(columnsMask)        
    
    for col in columnsMask:
        dataSet[col] = [] #we want a NEW empty list for each col, can't use fromkeys(columnsMask, [])
        
    for row in dictReader :
        for col in columnsMask:
            dataSet[col].append(float(row[col]))
            
    csvFile.close()
                
    return dataSet

def parse_halscope_log_abvt(fileName, path = _halscope_path):
    
    halFile = open(os.path.join(path, fileName), "r")
    
    halReader = csv.reader(halFile, delimiter=' ')
    
    dataSet = []
    halReader.next()
    halReader.next()
    for row in halReader:
        dataSet.append([float(row[1]), float(row[3]), float(row[5]), float(row[7])])
    
    dataSet.pop()
    
    return dataSet

def parse_halscope_log_xyzabvt(fileName, path = _halscope_path):
    
    halFile = open(os.path.join(path, fileName), "r")
    
    halReader = csv.reader(halFile, delimiter=' ')
    
    dataSet = []
    halReader.next()
    halReader.next()
    for row in halReader:
        dataSet.append([float(row[1]), float(row[3]), float(row[5]), float(row[7]), float(row[9]), float(row[11]), float(row[13])])
    
    dataSet.pop()
    
    return dataSet
            

def save_current_figure(fileName = "latest_plot.pdf"):
    
    plt.savefig(os.path.join(_plots_path, fileName), format="pdf")
        
    
    
    