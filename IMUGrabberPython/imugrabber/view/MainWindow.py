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

from PyQt4 import QtCore,QtGui
from imugrabber.view.autogen import Ui_MainWindow
import OpenGLWidget

from imugrabber.view import FlyingBox
from imugrabber.communication import Acquisition, AcquisitionThread

import PyIMUFiltering

from serial import Serial
#_SERIAL_PATH = '/dev/cp2102_2'
#_SERIAL_PATH = '/dev/cp2102_4'
#_SERIAL_PATH = '/dev/cp2102_3'
#_SERIAL_PATH = '/dev/ft232r_2'
_SERIAL_PATH = '/dev/ft232r_3'
#_SERIAL_PATH = '/dev/ft232r_4'
#_SERIAL_PATH = '/dev/ttyUSB1'
#_SERIAL_PATH = '/dev/ttyUSB0'
#_BAUDRATE = 2400
#_BAUDRATE = 9600
_BAUDRATE = 57600
#_BAUDRATE = 115200

class MainWindow(QtGui.QMainWindow, Ui_MainWindow.Ui_MainWindow):
    def __init__(self):
        QtGui.QMainWindow.__init__(self)
        
        self.setupUi(self)
        
#        self.machine = Machine.Machine(_iniFilePath)
#        self.modelListener = ModelListener.ModelListener(self.machine, 100)
#        
#        self.experimentScene = ExperimentSceneMock.ExperimentSceneMock()
#        self.experimentScene.setJoints(self.machine.joints['X'], self.machine.joints['Y'])
        
        
        
        self.flyingBox = FlyingBox.FlyingBox()
        
        ser = Serial(_SERIAL_PATH, baudrate=_BAUDRATE, bytesize=8, parity='N', stopbits=1, timeout=0.5, xonxoff=0, rtscts=0)
        acquisition = Acquisition.Acquisition(ser)
        filter = PyIMUFiltering.Filter()
        self.acquisitionThread = AcquisitionThread.AcquisitionThread(self.flyingBox, acquisition, filter)
        
        self.openGLWidget = OpenGLWidget.OpenGLWidget()
        self.openGLWidget.setSizePolicy(self.openGLView.sizePolicy())
        
        self.flyingBox.setObserver(self.openGLWidget)
        
        index = self.verticalLayout.indexOf(self.openGLView)
        stretch = self.verticalLayout.stretch(index)
        self.verticalLayout.removeWidget(self.openGLView)
        self.verticalLayout.insertWidget(index, self.openGLWidget)
#        self.verticalLayout.setStretch(index, stretch)
        self.verticalLayout.setStretch(0, 75)
        self.verticalLayout.setStretch(1, 25)
        
        self.acquisitionThread.start()

    def on_findMaxPosition_pressed(self):
        self.cal.setUp()
        self.cal.testfindMaxPosition()
#        pass
        