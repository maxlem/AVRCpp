'''
Created on 2009-12-09

@author: malem303
'''
import unittest
import time
import collections
from serial import Serial
from imugrabber.communication import Acquisition, Pattern
from imugrabber.algorithms import statistics, utils
from imugrabber.experiments import plots
from imugrabber.filtering import LowPassFilter
from imugrabber.communication.exceptions import Timeout

#_SERIAL_PATH = '/dev/cp2102_2'
_SERIAL_PATH = '/dev/cp2102_3'
#_SERIAL_PATH = '/dev/cp2102_4'

#_SERIAL_PATH = '/dev/ft232r_2'
#_SERIAL_PATH = '/dev/ft232r_3'
#_SERIAL_PATH = '/dev/ft232r_4'

#_SERIAL_PATH = '/dev/ttyUSB1'
#_SERIAL_PATH = '/dev/ttyUSB0'
#_BAUDRATE = 9600
_BAUDRATE = 57600
#_BAUDRATE = 115200
#_BAUDRATE = 230400

class PerformanceTest(unittest.TestCase):

    _PACKET_COUNT = 599
    
    def setUp(self):
        self.ser = Serial(_SERIAL_PATH, baudrate=_BAUDRATE, bytesize=8, parity='N', stopbits=1, timeout=0.1, xonxoff=0, rtscts=0)
        self.acquisition = Acquisition.Acquisition(self.ser)
#        self.acquisition = Acquisition.Acquisition(self.ser) 
#        self.packet, self.sample, self.ser = mocks.build_Acquisition_mocks()
#        self.acquisition = Acquisition.Acquisition(self.ser)


    def tearDown(self):
        pass

    def _testsendPattern(self):
        
        while(True):
            self.ser.write("________Pattern.6.6.xyzabc \n\n")
            time.sleep(.1)
        
    def testAcquisition(self):
        
#        while(True):
#            print self.ser.inWaiting()
        stdTotal = 0
        lastPacketID = None
        droppedPackets = 0
        
        self.acquisition.flushBuffer()
        beginTime = time.time()
        samplesByLabel = collections.defaultdict(list)
        self.acquisition.changePattern(Pattern.Pattern(patternName ="pkt", pattern = "abcxyzs", repetitions=PerformanceTest._PACKET_COUNT))
        
        filter = LowPassFilter.LowPassFilter(samplesByLabel)
        for i in range(PerformanceTest._PACKET_COUNT) :
            try:
                packet = self.acquisition.acquirePacket()
                
                
            except Timeout, t:
                print t
            except Exception, e:
                print e
            else :
                
                if(lastPacketID is not None):
                    if (packet.packetID != (lastPacketID + 1) % PerformanceTest._PACKET_COUNT):
                        droppedPackets += 1
                
                lastPacketID = packet.packetID
                
                if(packet.isCorrupt()) :
                    print "packet %d corrupt, checksum was %d" % (lastPacketID, packet.checksum)
                    
                else :
                
                    packet.toDict(samplesByLabel)
                    
                    
        
        statisticsByLabel = statistics.samplesMeanStandardDeviation(samplesByLabel)
        
        timeTotal = time.time() - beginTime
        
        print "---------------------------"
        
        for label, (mean, std) in statisticsByLabel.iteritems() :
            print "For label %c mean is %f, std is %f" % (label, mean, std)
            
        print "---------------------------"
        samplesCount = 0
        
        for label, samples in samplesByLabel.iteritems() :
            samplesCount += len(samples)
                        
        
        
        print "%i dropped packets, %d samples in %f seconds" % (droppedPackets, samplesCount, timeTotal)
        print "Effective sampling rate is %f Hz" % ((samplesCount/len(samplesByLabel.keys()))/timeTotal)
    



    def _testAcquisitionAndPlot(self):
        
        self.acquisition.flushBuffer()
        
        seconds = 50.0
        
        samplesByLabel = self.acquisition.acquireSamplesDuring(seconds)
        
#        io.serialize_results(samplesByLabel)

        
        utils.addTimestamps(samplesByLabel, 64.0/16.0e6, True)        

        self.assertAlmostEqual(utils.computeTimespan(samplesByLabel), seconds, 3)
        
        print utils.computeTimespan(samplesByLabel)
        plots.plot_samplesByLabel(samplesByLabel, 'timestamps')
        plots.show_figures()
        
    def _testCommunication(self):
        
        while(True):
            numberOfCharactersToRead = 10000
            
            beginTime = time.time()
            self.ser.flushInput()
            self.ser.read(numberOfCharactersToRead)
            endTime = time.time()
            
            print "read %d bytes in %f seconds: %f kbps at %f kbps speed " % (numberOfCharactersToRead, 
                                                                              endTime - beginTime, 
                                                                              numberOfCharactersToRead / ((endTime - beginTime)*1000), 
                                                                              float(_BAUDRATE)/1000/10)  

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testName']
    unittest.main()