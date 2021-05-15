#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# SlidePresenterView - Console for presenters 
# https://launchpad.net/slidepresenterview
#
# Copyright (C) 2009 Felix-Antoine Bourbonnais <bouf10pub _AT@. rubico.info>
# Copyright (C) 2009 Maxime Lemonnier <maxime.lemonnier _AT@. gmail.com>
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
"""
Generates .py file from resources (.ui and .qrc)
"""

import os
import sys

BASE_DIR = '../'
SOURCE_FOLDER = '' # Relative to BASE_DIR
PYUIC4_CMD = 'pyuic4'
PYRCC4_CMD = 'pyrcc4'

UI_DIR = 'resources/ui' # Relative to BASE_DIR
QRC_DIR = 'resources' # Relative to BASE_DIR

UI_OUTPUT_PREFIX = "Ui_"
QRC_OUTPUT_POSTFIX = '_rc'

OUT_PACKAGE = 'imugrabber.view.autogen' # Pkg. where .py will be generated

# pylint: disable-msg=C0103
_file_path = os.path.dirname(__file__)
_base_path = os.path.abspath(os.path.join(_file_path, BASE_DIR))
_src_path = os.path.join(_base_path, SOURCE_FOLDER)

def get_pyqt4_config():
    """@return: PyQt4 configuration dict"""
    try:
        import PyQt4.pyqtconfig
        return PyQt4.pyqtconfig.Configuration()
    except ImportError:
        print >> sys.stderr, "ERROR: PyQt4 not found."
        sys.exit(1)

def _get_files(extension, dir_):
    """
    @param extension: the extension (without the '.')
    @param dir: where to find files (relative to BASE_DIR and not recursive)
    @return: list of files names
    """
    
    full_path = os.path.join(_base_path, dir_)
    
    if not os.path.isdir(full_path):
        print >> sys.stderr, "WARN: Path %s is not a directory." % full_path
        return []
        
    files = [os.path.join(full_path, file_)
                   for file_ in os.listdir(full_path)
                   if file_.endswith('.%s' % extension)]
        
    return files
    
    
def _get_output_dir():
    """
    @return: The absolute path where .py should be generated.
    """
    dir_rel = OUT_PACKAGE.replace('.', os.path.sep)
    return os.path.join(_src_path, dir_rel)
    
            
def generate_ui_and_qrc(pyqt_bin_dir):
    """
    Generates .py for .ui and .qrc files
    @param pyqt_bin_dirparam: Qt binary directory
    """
    ui_files = _get_files('ui', UI_DIR)
    qrc_files = _get_files('qrc', QRC_DIR)
    out_dir = _get_output_dir()
    
    for ui_file in ui_files:
        file_name = os.path.basename(ui_file[:-3])
        file_name = "%s%s%s" % (UI_OUTPUT_PREFIX, file_name, ".py")
        vars_ = {'SRC': ui_file, 
                'DEST': os.path.join(out_dir, file_name),
                'CMD': os.path.join(pyqt_bin_dir, PYUIC4_CMD)}
        cmd = "%(CMD)s -o %(DEST)s %(SRC)s" % vars_
        
        print "Exec: %s" % cmd
        os.system(cmd)
        
    for qrc_file in qrc_files:
        file_name = os.path.basename(qrc_file[:-4])
        file_name = "%s%s%s" % (file_name, QRC_OUTPUT_POSTFIX, ".py")
        vars_ = {'SRC': qrc_file, 
                'DEST': os.path.join(out_dir, file_name),
                'CMD': os.path.join(pyqt_bin_dir, PYRCC4_CMD)}
        cmd = "%(CMD)s -o %(DEST)s %(SRC)s" % vars_
        
        print "Exec: %s" % cmd
        os.system(cmd)


if __name__ == '__main__':
    pyqtcfg = get_pyqt4_config() # pylint: disable-msg=C0103
    generate_ui_and_qrc(pyqtcfg.pyqt_bin_dir)