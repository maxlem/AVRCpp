'''
Created on 2010-01-22

@author: malem303
'''
from cgkit.cgtypes import *
import type_bug_pack


if __name__ == '__main__':
    
    m = mat3.fromEulerXYZ(0,0,0)
    
    print mat3
    print type(m)
    print isinstance(m, mat3)
    
    v = vec3(1)
    
    q = quat(2)
    
    v2 = q.rotateVec(v)
    
    print type(v)
    
    v3 = type_bug_pack.foo(v, v2)
    
    print type(v3)
    