'''
Created on 2009-05-26

@author: malem303
'''
import os,sys,math

# Import Qt modules
from PyQt4 import QtCore,QtGui

import MainWindow
             

def main():
     # Again, this is boilerplate, it's going to be the same on
     # almost every app you write
     app = QtGui.QApplication(sys.argv)
     window=MainWindow.MainWindow()
     window.show()
     # It's exec_ because exec is a reserved word in Python
     sys.exit(app.exec_())


if __name__ == '__main__':
    main()