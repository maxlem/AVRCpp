'''
Created on 2010-02-24

@author: malem303
'''

from imugrabber.experiments import plots

from serial import Serial

from pyemc.core import Machine, ModelListener
from imugrabber.experiments import Calibration
from imugrabber.communication import Acquisition, Pattern
from imugrabber.algorithms import statistics, io

_WORKSPACE_DIR = "../../../"
_CONFIG_DIR = "emc2-trunk/configs"
_INI_FILE = "sim/axis.ini"
#_iniFilePath = os.path.join(os.path.abspath(os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__), _WORKSPACE_DIR)), _CONFIG_DIR)), _INI_FILE)
_iniFilePath = "~/emc2/configs/univpwm-4-axis-xyab/univpwm.ini"
#_SERIAL_PATH = '/dev/cp2102_2'
#_SERIAL_PATH = '/dev/cp2102_4'
#_SERIAL_PATH = '/dev/cp2102_3'
#_SERIAL_PATH = '/dev/ft232r_2'
#_SERIAL_PATH = '/dev/ft232r_3'
#_SERIAL_PATH = '/dev/ft232r_4'
_SERIAL_PATH = '/dev/ttyUSB1'
#_SERIAL_PATH = '/dev/ttyUSB0'
#_BAUDRATE = 2400
#_BAUDRATE = 9600
_BAUDRATE = 57600
#_BAUDRATE = 115200



def buildAcquisition():
    ser = Serial(_SERIAL_PATH, baudrate=_BAUDRATE, bytesize=8, parity='N', stopbits=1, timeout=0.5, xonxoff=0, rtscts=0)
    acquisition = Acquisition.Acquisition(ser)
#    acquisition.changePattern(Pattern.Pattern(patternName="pkt", pattern="abcxyzs", repetitions=99))
    return acquisition

def buildCalibration():
    machine = Machine.Machine(_iniFilePath)
    modelListener = ModelListener.ModelListener(machine, 1)
    acquisition = buildAcquisition()
        
    longitudeGCodeLabel, latitudeGCodeLabel = 'z', 'a' 
#    longitudeGCodeLabel, latitudeGCodeLabel = 'x', 'y'
    calibration = Calibration.Calibration(acquisition, machine, longitudeGCodeLabel, latitudeGCodeLabel)
    
    
    
    return calibration, modelListener

def accelerometer_dataset():
    calibration, modelListener = buildCalibration()
    modelListener.start()
    longitudes = statistics.frange(-90.0, 45.0, 25)
    latitudes = statistics.frange(-180.0, 180.0, 50)
#    longitudes = statistics.frange(-5.0, 5.0, 5)
#    latitudes = statistics.frange(-10.0, 10.0, 5)
    
    dataSet = calibration.exploreUnitSphere(longitudes, latitudes)
    
    io.serialize_exploration(dataSet)
    
    dataSet = io.deserialize_exploration()

    print io.exploration_to_CSV(dataSet)
    
    return io.float_columns_from_CSV()








def gyro_dataset(misalignmentsAndScales = None, biases = None):
    acquisition = buildAcquisition()
    acquisition.flushBuffer()
    samplesByLabelBeforeMotion = acquisition.acquireSamplesDuring(5.0)
    
    acquisition.flushBuffer()
    samplesByLabelInMotion = acquisition.acquireSamplesDuring(5.0)
    
    dataSet = (samplesByLabelBeforeMotion, samplesByLabelInMotion)
    
#    io.serialize_results(dataSet)
    
    plots.plot_samplesByLabel(samplesByLabelInMotion, 's', ['b', 'c', 's', 't', 'timestamps', 'T', 'x', 'y', 'z'])
    plots.show_figures()
   
    
    return dataSet



