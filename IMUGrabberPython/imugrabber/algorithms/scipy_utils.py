'''
Created on 2010-01-20

@author: malem303
'''

import scipy as sp




def cross_matrix(lhsVector):
    return sp.array([[  0,            -lhsVector[2],    lhsVector[1]    ], 
                    [   lhsVector[2],  0,               -lhsVector[0]   ], 
                    [   -lhsVector[1], lhsVector[0],    0               ]])

def cross_product(lhs, rhs):
    
    crossMatrix = cross_matrix(lhs)
    
    return sp.dot(crossMatrix, rhs)

def to_quaternion(roll, pitch, yaw):
    quaternion = sp.zeros(4)
    quaternion[0] = sp.cos(roll/2)*sp.cos(pitch/2)*sp.cos(yaw/2) + sp.sin(roll/2)*sp.sin(pitch/2)*sp.sin(yaw/2)
    quaternion[1] = sp.sin(roll/2)*sp.cos(pitch/2)*sp.cos(yaw/2) - sp.cos(roll/2)*sp.sin(pitch/2)*sp.sin(yaw/2)
    quaternion[2] = sp.cos(roll/2)*sp.sin(pitch/2)*sp.cos(yaw/2) + sp.sin(roll/2)*sp.cos(pitch/2)*sp.sin(yaw/2)
    quaternion[3] = sp.cos(roll/2)*sp.cos(pitch/2)*sp.sin(yaw/2) - sp.sin(roll/2)*sp.sin(pitch/2)*sp.cos(yaw/2)
    return quaternion

def to_YPR(quaternion):
    q0, q1, q2, q3 = quaternion
    roll = sp.arctan2(2 * (q0*q1 + q2*q3), (q0**2 - q1**2 - q2**2 + q3**2))
    pitch = sp.arcsin(-2*(q1*q3 - q0*q2))
    yaw = sp.arctan2(2*(q1*q2 + q0*q3), (q0**2 + q1**2 - q2**2 - q3**2))

    return roll, pitch, yaw

def quternion_complement(quaternion):
    quaternion[1:4] *= -1
    
    return quaternion


def quaternion_norm(quaternion):
    
    return sum(quaternion**2)
    
def quaternion_product(lhs, rhs):
    a, A = lhs[0], lhs[1:4]
    b, B = rhs[0], rhs[1:4]
    
    c = a * b - sp.dot(A, B)
    C = sp.dot(a, B) + sp.dot(b,A) + cross_product(A,B)
    
    return sp.array([c, C[0], C[1], C[2]])


def quaternion_product_matrix(quaternion):
    
    q0, q1, q2, q3 = quaternion
    
    matrix = sp.zeros((4,4))
    
    matrix[0] = [q0, -q1, -q2, -q3 ]
    matrix[1] = [q1, q0, -q3, q2 ]
    matrix[2] = [q2, q3, q0, -q1 ]
    matrix[3] = [q3, -q2, q1, q0 ]
    
    return matrix
    
def quaternion_to_YPR_matrix(quaternion):
    
    q0, q1, q2, q3 = quaternion
    
    return sp.array([[(q0**2 + q1**2 - q2**2 - q3**2), 2*(q1*q2 + q0*q3), 2*(q1*q3 - q0*q2)],
                     [2*(q1*q2 - q0*q3), (q0**2 - q1**2 + q2**2 - q3**2), 2*(q2*q3 + q0*q1)],
                     [2*(q1*q3 + q0*q2), 2*(q2*q3 - q0*q1), (q0**2 - q1**2 - q2**2 + q3**2)]])

def YPR_matrix(roll, pitch, yaw):
    
    return sp.dot(roll_transform(roll), sp.dot(pitch_transform(pitch), yaw_transform(yaw)))


def roll_transform(roll):
    """
    Rotate frame around x axis
    """
    
    rotationMatrix = sp.diag([1.0, 1.0, 1.0])
    
    rotationMatrix[1,1], rotationMatrix[1,2] = sp.cos(roll), sp.sin(roll)
    
    rotationMatrix[2,1], rotationMatrix[2,2] = -sp.sin(roll), sp.cos(roll)
    
    return rotationMatrix

def pitch_transform(pitch):
    """
    Rotate frame around y axis
    """
    
    rotationMatrix = sp.diag([1.0, 1.0, 1.0])
    
    rotationMatrix[0,0], rotationMatrix[0,2] = sp.cos(pitch), -sp.sin(pitch)
    
    rotationMatrix[2,0], rotationMatrix[2,2] = sp.sin(pitch), sp.cos(pitch)
    
    return rotationMatrix

def yaw_transform(yaw):
    """
    Rotate frame around z axis
    """
    
    rotationMatrix = sp.diag([1.0, 1.0, 1.0])
    
    rotationMatrix[0,0], rotationMatrix[0,1] = sp.cos(yaw), sp.sin(yaw)
    
    rotationMatrix[1,0], rotationMatrix[1,1] = -sp.sin(yaw), sp.cos(yaw)
    
    return rotationMatrix

def quaternion_derivative(rollVelocity, pitchVelocity, yawVelocity, orientationQuaternion):
    
    velocityQuaternion = sp.array([0, rollVelocity, pitchVelocity, yawVelocity])
    
    return 0.5 * quaternion_product(orientationQuaternion, velocityQuaternion)


def d_rotation_d_q0(q0, q1, q2, q3):
    dR_dq0 = sp.zeros((3, 3))
    dR_dq0[0] = [q0, -q3, q2]
    dR_dq0[1] = [q3, q0, -q1]
    dR_dq0[2] = [-q2, q1, q0]
    return 2*dR_dq0


def d_rotation_d_q1(q0, q1, q2, q3):
    dR_dq1 = sp.zeros((3, 3))
    dR_dq1[0] = [q1, q2, q3]
    dR_dq1[1] = [q2, -q1, -q0]
    dR_dq1[2] = [q3, q0, -q1]
    return 2*dR_dq1


def d_rotation_d_q2(q0, q1, q2, q3):
    dR_dq2 = sp.zeros((3, 3))
    dR_dq2[0] = [-q2, q1, q0]
    dR_dq2[1] = [q1, q2, q3]
    dR_dq2[2] = [-q0, q3, -q2]
    return 2*dR_dq2


def d_rotation_d_q3(q0, q1, q2, q3):
    dR_dq3 = sp.zeros((3, 3))
    dR_dq3[0] = [-q3, -q0, q1]
    dR_dq3[1] = [q0, -q3, q2]
    dR_dq3[2] = [q1, q2, q3]
    return 2*dR_dq3

def d_inverse_rotation_d_quaternion_at(quaternion, vector):
    
    q0, q1, q2, q3 = quaternion
    
    jacobianTranspose = sp.zeros((4,3))
    
    dR_dq0 = d_rotation_d_q0(q0, q1, q2, q3).transpose()
    
    jacobianTranspose[0] = sp.dot(dR_dq0, vector)
    
    dR_dq1 = d_rotation_d_q1(q0, q1, q2, q3).transpose()
    
    jacobianTranspose[1] = sp.dot(dR_dq1, vector)
    
    dR_dq2 = d_rotation_d_q2(q0, q1, q2, q3).transpose()
    
    jacobianTranspose[2] = sp.dot(dR_dq2, vector)
    
    dR_dq3 = d_rotation_d_q3(q0, q1, q2, q3).transpose()
    
    jacobianTranspose[3] = sp.dot(dR_dq3, vector)
    
    return jacobianTranspose.transpose()

def d_rotation_d_quaternion_at(quaternion, vector):
    
    q0, q1, q2, q3 = quaternion
    
    jacobianTranspose = sp.zeros((4,3))
    
    dR_dq0 = d_rotation_d_q0(q0, q1, q2, q3)
    
    jacobianTranspose[0] = sp.dot(dR_dq0, vector)
    
    dR_dq1 = d_rotation_d_q1(q0, q1, q2, q3)
    
    jacobianTranspose[1] = sp.dot(dR_dq1, vector)
    
    dR_dq2 = d_rotation_d_q2(q0, q1, q2, q3)
    
    jacobianTranspose[2] = sp.dot(dR_dq2, vector)
    
    dR_dq3 = d_rotation_d_q3(q0, q1, q2, q3)
    
    jacobianTranspose[3] = sp.dot(dR_dq3, vector)
    
    return jacobianTranspose.transpose()
    
def load_submatrix(matrix, position, submatrix):
    
    rowIndex, colIndex = position
    rowsCount, colsCount = submatrix.shape
    for i in range(rowsCount) :
        matrix[rowIndex + i][colIndex:colIndex+colsCount] = submatrix[i]
        
        