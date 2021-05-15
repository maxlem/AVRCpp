# 
# QtEMC
#
# Copyright (C) 2009 Maxime Lemonnier <maxime.lemonnier _AT@. gmail.com>
# Took a lot of code from the original Axis (http://linuxcncn.org)  by (notably) 
# Jeff Epler and Chris Radek
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

import pygame
from pygame.locals import *
from cgkit.targetcamera import TargetCamera
from cgkit.camcontrol import CameraControl
from cgkit.eventmanager import *
from cgkit.glrenderer import GLRenderInstance, getScene
from cgkit.cgtypes import *
from cgkit.all import *

import os,sys,math
from PyQt4 import QtCore, QtGui, QtOpenGL
try:
    from OpenGL.GL import *
except ImportError:
    app = QtGui.QApplication(sys.argv)
    QtGui.QMessageBox.critical(None, "PyQtEMC - AxisGLWidget",
                            "PyOpenGL must be installed",
                            QtGui.QMessageBox.Ok | QtGui.QMessageBox.Default,
                            QtGui.QMessageBox.NoButton)
    sys.exit(1)


class OpenGLWidget(QtOpenGL.QGLWidget):
    def __init__(self, parent=None):
        
        QtOpenGL.QGLWidget.__init__(self, parent)
        
        self.width = 640
        self.height = 480
        self.scene = getScene()
        self.createCamera()
        self.createRenderer()
        self.eventmanager = eventManager()
        
        self.xRot = 0
        self.yRot = 0
        self.zRot = 0
        
    def notifySceneChanged(self):
        self.update()
        
    def createRenderer(self):
        self.renderer = GLRenderInstance()
        self.renderer.draw_solid = True
        self.renderer.draw_coordsys = True
        self.renderer.smooth_model = True
        self.renderer.backface_culling = False
        self.renderer.clearcol = vec4(self.scene.getGlobal("background", vec4(0.5, 0.5, 0.6, 0)))
    
    def createCamera(self):
        bbmin, bbmax = self.scene.boundingBox().getBounds()
        dif = bbmax - bbmin
        b1 = self.scene.up.ortho()
        b2 = self.scene.up.cross(b1)
        pos = dif.length() * (0.5 * b1 + b2) + (bbmax.z + 0.5 * dif.z) * self.scene.up
        if abs(dif.z) < 0.0001:
            pos += 0.8 * dif.length() * self.scene.up
        self.cam = TargetCamera(pos=pos, target=0.5 * (bbmin + bbmax) - 0.2 * (dif.z * self.scene.up), 
            fov=50)
        CameraControl(cam = self.cam, mode=None)
        
    def paintGL(self):
        self.renderer.setProjection(self.cam.projection(self.width, self.height, *self.cam.getNearFar()))
        self.renderer.setViewTransformation(self.cam.viewTransformation(), 0)
        self.renderer.paint(self.scene.worldRoot())

    def resizeGL(self, width, height):
        
        self.width = width
        self.height = height
        side = min(width, height)
        self.renderer.setViewport((width - side) / 2, (height - side) / 2, side, side)


    def mousePressEvent(self, event):
        x,y = event.pos().x(), event.pos().y()
        x0 = float(x)/self.width
        y0 = float(y)/self.height
        if event.button() == QtCore.Qt.LeftButton:
            self.eventmanager.event(LEFT_DOWN, MouseButtonEvent(1, x, y, x0, y0))
        elif event.button() == QtCore.Qt.RightButton:
            self.eventmanager.event(RIGHT_DOWN, MouseButtonEvent(3, x, y, x0, y0))
            
        self.lastPos = QtCore.QPoint(event.pos())
        
    def mouseReleaseEvent(self, event):
        
        if event.button() == QtCore.Qt.LeftButton:
            self.eventmanager.event(LEFT_UP, MouseButtonEvent(1, 0,0,0,0))
        elif event.button() == QtCore.Qt.RightButton:
            self.eventmanager.event(RIGHT_UP, MouseButtonEvent(3, 0,0,0,0))
        
        
    def mouseMoveEvent(self, event):
        x,y = event.pos().x(), event.pos().y()
        x0 = float(x)/self.width
        y0 = float(y)/self.height
        
        dx = event.x() - self.lastPos.x()
        dy = event.y() - self.lastPos.y()
        dx0 = float(dx)/self.width
        dy0 = float(dy)/self.height
        
        buttonsFlag = 0
        
        if event.buttons() & QtCore.Qt.LeftButton:
            buttonsFlag |= 1
        elif event.buttons() & QtCore.Qt.RightButton:
            buttonsFlag |= 4
        
        self.eventmanager.event(MOUSE_MOVE, MouseMoveEvent(x, y, dx, dy, x0, y0, dx0, dy0, buttonsFlag))

        self.updateGL()
        
        self.lastPos = QtCore.QPoint(event.pos())
        
    def wheelEvent(self, event):
        self.eventmanager.event(MOUSE_WHEEL, MouseWheelEvent(event.delta(), 0,0,0,0))
        self.updateGL()
