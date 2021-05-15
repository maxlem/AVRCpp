'''
Created on 2010-04-29

@author: malem303
'''

from cgkit.all import *

class FlyingBox(object):

    def __init__(self):
        

        self.box = Box(name = "box", lx=.1, ly=.1, lz=.1)
        self._position = [0,0,0]
        self.scale = 0.01
        
    @property
    def position(self):
        return self._position
    
    @position.setter
    def position(self, value):
        self._position = value
        self.box.pos = self.scale * vec3(*self._position)
        self.notifyObservers()
        
    def setObserver(self, observer):
        self.observer = observer
        
    def notifyObservers(self):
        if(self.observer is not None) :
            self.observer.notifySceneChanged()
        
        