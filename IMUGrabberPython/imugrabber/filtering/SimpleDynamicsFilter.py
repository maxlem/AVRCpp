'''
Created on 2010-01-18

@author: malem303
'''

import scipy as sp
from scipy import sin, cos, arcsin, arccos, arctan2, linalg
from imugrabber.algorithms import cgkit_to_scipy, scipy_utils
from cgkit.cgtypes import vec3, mat3, quat



        
class SimpleDynamicsFilter(object):
    
    def __init__(self):
        
        self._processCovariance = sp.identity(13)
        
        self._measurementCovariance = sp.identity(3)
        
        self._errorCovariance = sp.identity(13)
        
        self._translationRotorFromBody = vec3(0)
         
        self._gravity = vec3([0.0, 0.0, 1.0])
        
        self._magneticField = mat3.fromEulerXYZ(0.0, -1.22, 0.0) * vec3([1.0, 0.0, 0.0])
        # the magnetic field vector points to the magnetic north, with a -70 degrees (-1.22 radians) pitch (towards the ground)
        
        self._declinationAngle = 0.0
        
        self.timestamp = 0.0
        
        self.positionNED = vec3(0)
        
        self.velocityBody = vec3(0)
        
        self.orientationBody = quat(1)
        
        self.gyroBiases = vec3(0)
        
        self.gravityBody = self._gravity
        

        

    def _integrateAngularVelocities(self, angularVelocity, timeElapsed):
        
        angularVelocityQuat = quat(0.0, angularVelocity.x, angularVelocity.y, angularVelocity.z)
        
        self.orientationBody = self.orientationBody * (angularVelocityQuat * timeElapsed / 2).exp()



    def _predictLinearAccelerationFromGravityAndAngularVelocity(self, angularVelocity):
        
        predictedGravity = self.orientationBody.conjugate().rotateVec(self._gravity)
        
        predictedCentripetalAcceleration = angularVelocity.cross(self.velocityBody)
        
        predictedRotorOffsetCentripetalAcceleration = angularVelocity.cross(angularVelocity.cross(self._translationRotorFromBody))
        
        return predictedGravity + predictedCentripetalAcceleration + predictedRotorOffsetCentripetalAcceleration

    def _computeLinearAcceleration(self, acceleration, angularVelocity):
        
        linearAcceleration = acceleration - self._predictLinearAccelerationFromGravityAndAngularVelocity(angularVelocity)
        
        return linearAcceleration


    def _integrateAccelerations(self, acceleration, angularVelocity, timeElapsed):
        
        self.velocityBody = self.velocityBody + self._computeLinearAcceleration(acceleration, angularVelocity) * timeElapsed


    def _integrateLinearVelocities(self, timeElapsed):
        
        self.positionNED = self.positionNED + self.orientationBody.rotateVec(self.velocityBody) * timeElapsed

    def transition(self, acceleration, angularVelocity, timestamp):
        
        timeElapsed = timestamp - self.timestamp
        
        self._integrateAngularVelocities(angularVelocity, timeElapsed)
        
        self._integrateAccelerations(acceleration, angularVelocity, timeElapsed)
        
        self._integrateLinearVelocities(timeElapsed)
        
        self.timestamp = timestamp 
        
        jacobian = self._computeJacobian(angularVelocity)
        
        self._errorCovariance = self._errorCovariance + timeElapsed * (sp.dot(jacobian, self._errorCovariance) + sp.dot(self._errorCovariance, jacobian.transpose()) + self._processCovariance)
    

    def _predictMagnetoBody(self):
        predictedMagneto = self.orientationBody.rotateVec(self._magneticField)
        return predictedMagneto

    def measure(self, magneto):
        
        measurementJacobian = sp.zeros((3,13))
        
        magnetoJacobian = scipy_utils.d_inverse_rotation_d_quaternion_at(cgkit_to_scipy.convert(self.orientationBody), cgkit_to_scipy.convert(magneto))
        
        scipy_utils.load_submatrix(measurementJacobian, (0, 6), magnetoJacobian)
        
        kalmanGain = sp.dot(sp.dot(self._errorCovariance, measurementJacobian.transpose()),linalg.inv(sp.dot(measurementJacobian, sp.dot(self._errorCovariance, measurementJacobian.transpose())) + self._measurementCovariance))
        
        stateCorrection = sp.dot(kalmanGain, (cgkit_to_scipy.convert(magneto - self._predictMagnetoBody())))
        
        self.orientationBody = self.orientationBody + quat(list(stateCorrection[6:10]))
        
        self._errorCovariance = sp.dot((sp.identity(13) - sp.dot(kalmanGain, measurementJacobian)), self._errorCovariance)
        
        
        
    def _computeJacobian(self, angularVelocity):
        
        jacobian = sp.zeros((13, 13))
        
        scipy_utils.load_submatrix(jacobian, (0, 3), cgkit_to_scipy.convert(self.orientationBody.toMat3()))
        
        scipy_utils.load_submatrix(jacobian, (3, 3), -scipy_utils.cross_matrix(self.velocityBody))
        
        velocityOrientationJacobian = scipy_utils.d_rotation_d_quaternion_at(cgkit_to_scipy.convert(self.orientationBody), cgkit_to_scipy.convert(self.velocityBody))
        
        scipy_utils.load_submatrix(jacobian, (0, 6), velocityOrientationJacobian)
        
        accelerationOrientationJacobian = - scipy_utils.d_inverse_rotation_d_quaternion_at(cgkit_to_scipy.convert(self.orientationBody), cgkit_to_scipy.convert(self._gravity))
        
        scipy_utils.load_submatrix(jacobian, (3, 6), accelerationOrientationJacobian)
        
        angularVelocityQuaternion = sp.zeros(4)
        
        angularVelocityQuaternion[1:] = cgkit_to_scipy.convert(angularVelocity)
        
        angularVelocityOrientationJacobian = 0.5 * scipy_utils.quaternion_product_matrix(angularVelocityQuaternion)
        
        scipy_utils.load_submatrix(jacobian, (6, 6), angularVelocityOrientationJacobian)
        
        orientationQuaternionMatrix = 0.5 * scipy_utils.quaternion_product_matrix(cgkit_to_scipy.convert(self.orientationBody))
        
        gyroBiasPropagation =  orientationQuaternionMatrix.transpose()[1:]
        
        scipy_utils.load_submatrix(jacobian, (3, 10), gyroBiasPropagation.transpose())
        
        return jacobian
