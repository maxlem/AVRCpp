'''
Created on 2009-05-30

@author: malem303
'''
import exceptions

class CheckSumError(Exception):
    '''
    classdocs
    '''

    def __init__(self, details, tuple):
        '''
        Constructor
        '''
        self.name = "CheckSumError"
        self.details = details
        self.tuple = tuple
    
    def __str__(self):
        return repr(self.name) + repr(self.details) + repr(self.tuple)

class Timeout(Exception):
    '''
    classdocs
    '''

    def __init__(self, details = ""):
        '''
        Constructor
        '''
        self.name = "Timeout"
        self.details = details
    
    def __str__(self):
        return repr(self.name) + repr(self.details)
    
