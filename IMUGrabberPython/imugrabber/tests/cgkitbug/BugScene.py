'''
Created on 2009-12-03

@author: malem303
'''
import pygame
from pygame.locals import *
from cgkit.all import *
import math

class BugScene(object):
    '''
    classdocs
    '''

    GVectorWorldCoords = vec4(0, 0, -1.0, 0.0)
    
    def __init__(self):
        '''
        Constructor
        '''
        self.base = Box(name = "TaigBed", lx=15.0, ly=4.0, lz=1.5)
        self._baseRotXYZAngles = mat3(1.0)
        
        self.rotativePivotA = Torus(name = "RotativeTableA", major=3.0, parent=self.base)
        self.rotativeTableA = Box(name = "RotativeBedA", lx=self.base.lx, ly=self.base.ly, lz=1, parent=self.rotativePivotA)
        
        self._rotativeTableAAngle = 0
        
        self.rotativePivotB = Torus(name = "RotativeTableB", major=3.0, parent=self.rotativeTableA)
        self.rotativeTableB = Box(name = "RotativeBedB", lx=self.base.ly, ly=self.base.ly, lz=1, parent=self.rotativePivotB)
        self._rotativeTableBAngle = 0
        
        self.rebuild()
    
    @property
    def baseRotationMat3(self):
        return self._baseRotXYZAngles
    
    @baseRotationMat3.setter
    def baseRotationMat3(self, value):
        self._baseRotXYZAngles = value
        self.rebuild()
    
    @property
    def rotativeTableAAngle(self):
        return self._rotativeTableAAngle
    
    @rotativeTableAAngle.setter
    def rotativeTableAAngle(self, angle):
        self._rotativeTableAAngle = angle
        self.rebuild()
    
    @property
    def rotativeTableBAngle(self):
        return self._rotativeTableBAngle
    
    @rotativeTableBAngle.setter
    def rotativeTableBAngle(self, angle):
        self._rotativeTableBAngle = angle
        self.rebuild()
        

    def updateRotativePivotATransform(self):
        rotativeTableATramsform = mat4(1.0)
        rotativeTableATramsform.setMat3(mat3.fromEulerXYZ(0, math.pi / 2, 0))
        rotativeTableATramsform.translate(vec3(-3, 0, -self.base.lx / 2))
        self.rotativePivotA.transform = rotativeTableATramsform


    def updateRotativeTableATransform(self):
        rotativeBedATramsform = mat4(1.0)
        rotativeBedATramsform.setMat3(mat3.fromEulerZYX(self._rotativeTableAAngle, -math.pi / 2, 0))
        rotativeBedATramsform.translate(vec3(self.base.lx / 2, 0, 0))
        self.rotativeTableA.transform = rotativeBedATramsform


    def updateRotativePivotBTransform(self):
        rotativeTableBTramsform = mat4(1.0)
        rotativeTableBTramsform.setMat3(mat3.fromEulerXYZ(math.pi / 2, 0, 0))
        rotativeTableBTramsform.translate(vec3(0, 3, -self.base.ly / 2))
        self.rotativePivotB.transform = rotativeTableBTramsform


    def updateRotativeTableBTransform(self):
        rotativeBedBTramsform = mat4(1.0)
        rotativeBedBTramsform.setMat3(mat3.fromEulerXYZ(-math.pi / 2, self._rotativeTableBAngle, 0))
        rotativeBedBTramsform.translate(vec3(0, -self.base.ly / 2, 0))
        self.rotativeTableB.transform = rotativeBedBTramsform


    def updateBaseTransform(self):
        self.base.rot = self._baseRotXYZAngles

    def rebuild(self):
        
        
        
        self.updateBaseTransform()    
        
        self.updateRotativePivotATransform()
        
        self.updateRotativeTableATransform()
        
        self.updateRotativePivotBTransform()
        
        self.updateRotativeTableBTransform()
        
        
        
        
        
        
    def gVectorInTableBCoords(self):
        
        t = self.rotativeTableB.worldtransform
        return t * BugScene.GVectorWorldCoords
        
