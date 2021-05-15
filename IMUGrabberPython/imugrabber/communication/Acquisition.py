'''
Created on 2009-12-16

@author: malem303
'''
'''
Created on 2009-05-26

@author: malem303

'''
import time
import collections
from exceptions import Timeout
from imugrabber.communication import Pattern, Packet

class Acquisition(object):
    
    def __init__(self, serialDevice, timeout = 0.5):
        
        self.serialDevice = serialDevice
        
        self.timeout = timeout
        
        self.pattern = Pattern.Pattern()
        
        self.currentReadBuffer = ""
                      
        
    def matchPattern(self):    
        
        packetRegexMatch = None
        
        timeout = time.time() + self.timeout
        
        while (packetRegexMatch is None):
            
            justRead = self.serialDevice.read(5)
            
            if (time.time() > timeout):
                raise Timeout("No pattern matched in %f seconds, aborting" % (time.time() - timeout + self.timeout))
            
            self.currentReadBuffer = "%s%s" % (self.currentReadBuffer, justRead)
            
            packetRegexMatch = self.pattern.match(self.currentReadBuffer)
                    
            
        
        self.currentReadBuffer = self.currentReadBuffer[packetRegexMatch.end():]
        
        return packetRegexMatch

    def changePattern(self, pattern) :
        
        self.pattern = pattern
        
        while(True) :
            
            self.serialDevice.write(self.pattern.buildChangePatternCommand())
            
            try:
                self.matchPattern()
            finally:
                break;
        
        self.currentReadBuffer = ""
        

    def flushBuffer(self):
        
        self.serialDevice.flushInput()
        
        self.currentReadBuffer = ""
    

    def acquirePacket(self):
        
        return Packet.Packet(*self.pattern.extractPattern(self.matchPattern()))    
    

    def acquireNSamples(self, samplesCount, labels = "xyz"):
        
        samplesByLabel = collections.defaultdict(list)
        
        labels = list(labels)
        
        while len(labels) > 0:
            
            packet = self.acquirePacket()
            
            if(not packet.isCorrupt()) :
                packet.toDict(samplesByLabel)
                
            for label in labels:
                if len(samplesByLabel[label]) > samplesCount :
                    labels.remove(label)
                        
        return samplesByLabel
    
    def acquireSamplesDuring(self, seconds = 1.0):
        
        
        packets = []
        stopTime = time.time() + seconds
        while time.time() < stopTime:
            packets.append(self.acquirePacket())
            

        previousPacketID = None
        
        lostPackets = 0
        
        samplesByLabel = collections.defaultdict(list)
        
        for packet in packets :
            
            if(packet.isCorrupt()) :
                print "Packet %d is corrupt " % packet.packetID
                continue
            
            if previousPacketID is not None :
                
                expectedPacketID = (previousPacketID + 1) % (self.pattern.repetitions)
                
                if packet.packetID != expectedPacketID:
                    print "Packet ID is %d, previous packet ID was %d" % (packet.packetID, previousPacketID)
                    
                    if(packet.packetID > previousPacketID) :
                        lostPackets += packet.packetID - expectedPacketID
                    else:
                        lostPackets += (self.pattern.repetitions - 1) + packet.packetID - expectedPacketID
                    
            
            previousPacketID = packet.packetID
            
            packet.toDict(samplesByLabel)
            
        print "Acquired %d packets, lost %d packets" % (len(packets), lostPackets) 
        
        return samplesByLabel
        