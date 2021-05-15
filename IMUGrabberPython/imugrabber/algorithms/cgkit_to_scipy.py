'''
Created on 2010-01-20

@author: malem303
'''

import scipy as sp
from cgkit._core import vec3, vec4, mat3, mat4, quat

def _convert_mat(to_convert, rows, cols):
    
    converted = sp.zeros((rows, cols))
    
    for row in range(rows):
        for col in range(cols):
            converted[row, col] = to_convert[row, col]
    
    return converted

def _convert_vec(to_convert, size):
    
    converted = sp.zeros(size)
    
    for i in range(size):
        converted[i] = to_convert[i]
    
    return converted

def _convert_quat(to_convert):
    
    converted = sp.zeros(4)
    
    converted[0] = to_convert.w
    converted[1] = to_convert.x
    converted[2] = to_convert.y
    converted[3] = to_convert.z
    
    return converted

def convert(to_convert):
    
    if isinstance(to_convert, vec3) :
        return _convert_vec(to_convert, 3)
    elif isinstance(to_convert, vec4) :
        return  _convert_vec(to_convert, 4)
    elif isinstance(to_convert, mat3) :
        return  _convert_mat(to_convert, 3, 3)
    elif isinstance(to_convert, mat4) :
        return  _convert_mat(to_convert, 4, 4)
    elif isinstance(to_convert, quat) :
        return  _convert_quat(to_convert)
    
    