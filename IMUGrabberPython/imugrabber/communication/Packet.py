'''
Created on 2010-02-20

@author: malem303
'''

import collections

class Packet(object):
    '''
    classdocs
    '''

    def __init__(self, samples, info):
        '''
        Constructor
        '''
        self.samples, (self.patternName, self.packetID, self.checksum) = samples, info
    
    def isCorrupt(self):
        
        return self.checksum != 0
    
    def toDict(self, samplesByLabel = None):
        
        if samplesByLabel is None :
            samplesByLabel = collections.defaultdict(list)
        
        for (label, sample) in self.samples :
            samplesByLabel[label].append(sample)
            
        return samplesByLabel
    
