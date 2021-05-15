'''
Created on 2009-09-01

@author: malem303
'''
import unittest
from serial import Serial
import time
from parallel import Parallel

_SERIAL_PATH = '/dev/cp2102_3'
#_SERIAL_PATH = '/dev/ttyUSB1'
_BAUDRATE = 57600
#_BAUDRATE = 115200
_READ_MARGIN = 10

class USARTTest(unittest.TestCase):

    par = Parallel()

    def __init__(self, *args):
        unittest.TestCase.__init__(self, *args)
        self.ser = Serial(_SERIAL_PATH, baudrate=_BAUDRATE, bytesize=8, parity='N', stopbits=1, timeout=1, xonxoff=0, rtscts=0)
        self._toWrite = "Write_TEST123"
        self._toRead = "Read_TEST123"
        
          
    def testread(self):
        time.sleep(0.1)
        USARTTest.par.setData(0x01)
        time.sleep(0.1)
        self.ser.write(self._toRead + '\n')
        USARTTest.par.setData(0x00)
        
        
        print "See avr console..."
        
    def testwrite(self):
        time.sleep(0.1)
        USARTTest.par.setData(0x01)
        line = self.ser.readline(len(self._toWrite) + 1,'\n')
        USARTTest.par.setData(0x00)
        
        self.assertNotEqual(len(line), 0)
        
        self.assertNotEqual(line.find(self._toWrite), -1, "Received %s" % line)
        




if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()
