'''
Created on 2009-12-03

@author: malem303
'''
from cgkit.all import *
import math


class ExperimentSceneMock(object):
    '''
    classdocs
    '''

    GVectorWorldCoords = vec4(0, 0, -1.0, 0.0)
 
    def __init__(self):
        '''
        Constructor
        '''        
        self.jointA = None
        self.jointB = None
        self.observer = None
        
        self.base = Box(name = "Base", lx=15.0, ly=4.0, lz=1.5)
        self.baseXYZAngles = (0,0,0) 
        
        self.rotativePivotA = Torus(name = "RotativeTableA", major=3.0, parent=self.base)
        rotativeTableATramsform = mat4(1.0)
        rotativeTableATramsform.setMat3(mat3.fromEulerXYZ(0, math.pi / 2, 0))
        rotativeTableATramsform.translate(vec3(-3, 0, -self.base.lx / 2))
        self.rotativePivotA.transform = rotativeTableATramsform

        
        self.rotativeTableA = Box(name = "RotativeBedA", lx=self.base.lx, ly=self.base.ly, lz=1, parent=self.rotativePivotA)
        self.rotativeTableAAngle = 0
        
        self.rotativePivotB = Torus(name = "RotativeTableB", major=3.0, parent=self.rotativeTableA)
        rotativeTableBTramsform = mat4(1.0)
        rotativeTableBTramsform.setMat3(mat3.fromEulerXYZ(math.pi / 2, 0, 0))
        rotativeTableBTramsform.translate(vec3(0, 3, -self.base.ly / 2))
        self.rotativePivotB.transform = rotativeTableBTramsform

        
        self.rotativeTableB = Box(name = "RotativeBedB", lx=self.base.ly, ly=self.base.ly, lz=1, parent=self.rotativePivotB)
        self.rotativeTableBAngle = 0
        
        
        self.imu = Box(name = "imu", lx=1, ly=1, lz=1, parent=self.rotativeTableB, material=GLMaterial( diffuse = (1,0,0) ))
        self.imuXYZAngles = (0,0,0)
        
        self.imuX = Draw(name = "imuX", parent=self.imu)
        self.imuX.line(vec3(0), vec3(1,0,0), (1,0,0), 5)
        
        self.imuY = Draw(name = "imuY", parent=self.imu)
        self.imuY.line(vec3(0), vec3(0,1,0), (0,1,0), 5)
        
        self.imuZ = Draw(name = "imuZ", parent=self.imu)
        self.imuZ.line(vec3(0), vec3(0,0,1), (0,0,1), 5)         
        

                
    def setJoints(self, jointA, jointB):
        
        self.jointA = jointA
        self.jointA.addWriteObserver(self)
        self.jointB = jointB
        self.jointB.addWriteObserver(self)
        self.notifyWrite()
    
    def setObserver(self, observer):
        self.observer = observer
        
    def notifyWrite(self):
        self.rotativeTableAAngle = math.radians(self.jointA.position)
        self.rotativeTableBAngle = math.radians(self.jointB.position)
    
    @property
    def baseXYZAngles(self):
        return self._baseXYZAngles
    
    @baseXYZAngles.setter
    def baseXYZAngles(self, value):
        self._baseXYZAngles = value
        self.base.rot = mat3.fromEulerXYZ(*self._baseXYZAngles)
        self.notifyObservers()
            
    @property
    def rotativeTableAAngle(self):
        return self._rotativeTableAAngle
    
    @rotativeTableAAngle.setter
    def rotativeTableAAngle(self, angle):
        self._rotativeTableAAngle = angle
        rotativeBedATramsform = mat4(1.0)
        rotativeBedATramsform.setMat3(mat3.fromEulerZYX(self._rotativeTableAAngle, -math.pi / 2, 0))
        rotativeBedATramsform.translate(vec3(self.base.lx / 2, 0, 0))
        self.rotativeTableA.transform = rotativeBedATramsform

        self.notifyObservers()
    
    @property
    def rotativeTableBAngle(self):
        return self._rotativeTableBAngle
    
    @rotativeTableBAngle.setter
    def rotativeTableBAngle(self, angle):
        self._rotativeTableBAngle = angle
        rotativeBedBTramsform = mat4(1.0)
        rotativeBedBTramsform.setMat3(mat3.fromEulerXYZ(-math.pi / 2, self._rotativeTableBAngle, 0))
        rotativeBedBTramsform.translate(vec3(0, -self.base.ly / 2, 0))
        self.rotativeTableB.transform = rotativeBedBTramsform

        self.notifyObservers()
        
    @property
    def imuXYZAngles(self):
        return self._imuXYZAngles
    
    @rotativeTableBAngle.setter
    def imuXYZAngles(self, xyzAngles):
        self._imuXYZAngles = xyzAngles
        imuTransform = mat4(1.0)
        imuTransform.setMat3(mat3.fromEulerXYZ(*self._imuXYZAngles))
        imuTransform.translate(vec3(0,0,self.rotativeTableB.lz))
        self.imu.transform = imuTransform

        self.notifyObservers()
        
    def notifyObservers(self):
        if(self.observer is not None) :
            self.observer.notifySceneChanged()
        
        

    def gVectorInIMUCoords(self):
        
        ''' worldtransform gives use the transformation we must apply to an object to rotate and translate it in world coords
            the transform we must apply to a vector in world coords to express it in object's local coords system is worldtransform.inverse
        '''
        gVector4 = self.imu.worldtransform.inverse() * ExperimentSceneMock.GVectorWorldCoords
        return vec3(gVector4[0], gVector4[1], gVector4[2])
        
