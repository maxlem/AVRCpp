'''
Created on 2010-08-22

@author: malem303
'''

from imugrabber.communication import Acquisition, Pattern
from serial import Serial




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



if __name__ == '__main__':
    
    acquisition = buildAcquisition()
    
    while (True) :
        packet = acquisition.acquirePacket()
        
        print packet.toDict()
    