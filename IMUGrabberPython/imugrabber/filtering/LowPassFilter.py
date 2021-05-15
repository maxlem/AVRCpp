'''
Created on 2010-02-20

@author: malem303
'''

import collections
from imugrabber.algorithms import statistics

#        domainByLabel = {'a':(0,2**10), 'b':(0,2**10), 'c':(0,1024), 'x':(0,2**10), 'y':(0,2**10), 'z':(0,2**10), 't':(0,2**26), 'T':(0,2**16), 's':(0, 2**32)}, 
 

class LowPassFilter(object):
    '''
    classdocs
    '''


    def __init__(self, samplesByLabel, historySize = 5):
        '''
        Constructor
        '''
        self.samplesByLabel = samplesByLabel
        self.historySize = historySize
        
    
    def filterSamples(self, samplesByLabel):

        samplesByLabelHistory = collections.defaultdict(list)
        
        for label, samples in self.samplesByLabel.iteritems() :
            if(len(samples) >= self.historySize):
                samplesByLabelHistory[label].extend(samples[-5,:])
            else :
                for label, samples in samplesByLabel.iteritems() :
                    self.samplesByLabel[label].extend(samples)
                return
        
        statisticsByLabelHistory = statistics.samplesMeanStandardDeviation(samplesByLabelHistory)
        
        for label, samples in samplesByLabel.iteritems() :
            for sample in samples :
                mean, std = statisticsByLabelHistory[label]
                if(mean - 2 * std < sample and sample < mean + 2 * std) :
                    self.samplesByLabel[label].append(sample)
            
        return samplesByLabel