'''
Created on 2010-03-12

@author: malem303
'''

import struct
import re
import array
import math
import collections

def _compute_checksum(bytes, checksumFormat):

    chunks = array.array(checksumFormat, bytes)
    
    checksumMax = struct.calcsize(checksumFormat) * int(math.pow(2, 8))

    chunksSum = sum(chunks) % checksumMax
    
    checksum = (checksumMax - chunksSum) % checksumMax
    
    return checksum

class Pattern(object):
    '''
    classdocs
    '''


    def __init__(self,  patternName = "dft", 
                        pattern = "xyzabcs",
                        repetitions = 100, 
                        formatByLabel = {'a':'H', 'b':'H', 'c':'H', 'x':'H', 'y':'H', 'z':'H', 't':'H', 'T':'H', 's':'L'},
                        checksumFormat = 'B'):
        
        self.patternName = patternName
        self.pattern = list(pattern)
        self.repetitions = repetitions
        self.formatByLabel = formatByLabel
        self.checksumFormat = checksumFormat
        self.format = ""
        
        for label in self.pattern:
            self.format += self.formatByLabel[label]
        
        self.format += checksumFormat
        
        self.formatSize = struct.calcsize(self.format)
        
        self.typicalPacketSize = len("__ :%s:%d: __" % (self.patternName, self.repetitions) ) + self.formatSize
        
        self.packetRegex = re.compile(":(?P<patternName>%s):(?P<packetID>[\d]+[\0]*):[\0]{1}(?P<data>.{%d}):" % (self.patternName, self.formatSize), re.MULTILINE | re.DOTALL)

    def buildChangePatternCommand(self):
        
        return "__Pattern:%s:%d:%d:%s \n\n" % (self.patternName, self.repetitions, len(self.pattern), "".join(self.pattern))
    
    def match(self, input):
        
        return self.packetRegex.search(input)
        
    
    def extractPattern(self, regexMatch):
        
        patternName = regexMatch.group('patternName')
        
        packetID = int(regexMatch.group('packetID'))
        
        data = regexMatch.group('data')
        
        checksum = _compute_checksum(data, self.checksumFormat)
        
        unpackedValues = struct.unpack(self.format, data)   
        
        samples = []
        
        index = 0
        
        for label in self.pattern:
            
            sample = unpackedValues[index]
            samples.append((label,sample))
            index += 1     
        
        info = (patternName, packetID, checksum)
        
        return samples, info
        
        

        