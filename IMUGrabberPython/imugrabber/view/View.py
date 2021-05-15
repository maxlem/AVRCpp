'''
Created on 2009-12-03

@author: malem303
'''
#!/usr/bin/env python
# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is the Python Computer Graphics Kit.
#
# The Initial Developer of the Original Code is Matthias Baas.
# Portions created by the Initial Developer are Copyright (C) 2004
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****
# $Id: viewer.py,v 1.13 2006/03/03 09:13:59 mbaas Exp $

import pygame
from pygame.locals import *
from cgkit.targetcamera import TargetCamera
from cgkit.camcontrol import CameraControl
from cgkit.eventmanager import *
from cgkit.glrenderer import GLRenderInstance, getScene
from cgkit.cgtypes import *
from cgkit.all import *

class View(object):
    """The Main PyMan Class - This class handles the main 
    initialization and creating of the Game."""
    

    def __init__(self, width=640,height=480):
        
        self.width = width
        self.height = height  
             
        self.createPygameScreen()
        self.scene = getScene()
        self.createCamera()
        self.createRenderer()
        self.createKeyDict()
        self.running = True
        

                
    def refresh(self):
        
        self.draw()
        pygame.display.flip()
        self.handleEvents(pygame.event.get())

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


    def createPygameScreen(self):
        pygame.init()
        pygame.display.set_caption("OpenGL viewer")
        flags = OPENGL | DOUBLEBUF
        self.screen = pygame.display.set_mode((self.width, self.height), flags)


    def createRenderer(self):
        self.renderer = GLRenderInstance()
        self.renderer.left_handed = self.scene.handedness == "l"
        self.renderer.setViewport(0, 0, self.width, self.height)
        self.renderer.draw_solid = True
        self.renderer.draw_coordsys = True
        self.renderer.smooth_model = True
        self.renderer.backface_culling = False
        self.renderer.clearcol = vec4(self.scene.getGlobal("background", vec4(0.5, 0.5, 0.6, 0)))
        
    def draw(self):
    
        P = self.cam.projection(self.width, self.height, *self.cam.getNearFar())
        self.renderer.setProjection(P)
    
        self.renderer.setViewTransformation(self.cam.viewTransformation(), 0)
    
        self.renderer.paint(self.scene.worldRoot())
    
    def convertMods(self, mods):
        """Convert pygame key modifier flags to cgkit modifier flags.
        """
        res = 0
        if mods & 0x0001 or mods & 0x0002:
            res |= KEYMOD_SHIFT
        if mods & 0x0040 or mods & 0x0080:
            res |= KEYMOD_CONTROL
        if mods & 0x0100 or mods & 0x0200:
            res |= KEYMOD_ALT
        return res
    
    def handleEvents(self, events):
        eventmanager = eventManager()
        for e in events:
            if e.type==QUIT:
                self.running=False
            # KEYDOWN?
            elif e.type==KEYDOWN:
                if e.key==27:
                    self.running=False
                key = e.unicode
                code = self.keydict.get(e.key, e.key)
                mods = self.convertMods(e.mod)
                eventmanager.event(KEY_PRESS, KeyEvent(key, code, mods))
#                keyboard.setKeyValue(e.key, True)
            # KEYUP
            elif e.type==KEYUP:
                code = self.keydict.get(e.key, e.key)
                try:
                    key = unicode(chr(e.key))
                except:
                    key = u""
                mods = self.convertMods(e.mod)
                eventmanager.event(KEY_RELEASE, KeyEvent(key, code, mods))
#                keyboard.setKeyValue(e.key, False)
            # MOUSEBUTTONDOWN
            elif e.type==MOUSEBUTTONDOWN:
                x,y = e.pos
                x0 = float(x)/self.width
                y0 = float(y)/self.height
                if e.button==1:
                    eventname = LEFT_DOWN
                    evt = MouseButtonEvent(e.button, x, y, x0, y0)
                elif e.button==2:
                    eventname = MIDDLE_DOWN
                    evt = MouseButtonEvent(e.button, x, y, x0, y0)
                elif e.button==3:
                    eventname = RIGHT_DOWN
                    evt = MouseButtonEvent(e.button, x, y, x0, y0)
                elif e.button==4:
                    eventname = MOUSE_WHEEL
                    evt = MouseWheelEvent(120, x, y, x0, y0)
                elif e.button==5:
                    eventname = MOUSE_WHEEL
                    evt = MouseWheelEvent(-120, x, y, x0, y0)
                else:
                    eventname = MOUSE_BUTTON_DOWN
                    evt = MouseButtonEvent(e.button, x, y, x0, y0)
                eventmanager.event(eventname, evt)
            # MOUSEBUTTONUP
            elif e.type==MOUSEBUTTONUP:
                x,y = e.pos
                x0 = float(x)/self.width
                y0 = float(y)/self.height
                if e.button==1:
                    eventname = LEFT_UP
                    evt = MouseButtonEvent(e.button, x, y, x0, y0)
                elif e.button==2:
                    eventname = MIDDLE_UP
                    evt = MouseButtonEvent(e.button, x, y, x0, y0)
                elif e.button==3:
                    eventname = RIGHT_UP
                    evt = MouseButtonEvent(e.button, x, y, x0, y0)
                elif e.button==4:
                    eventname = MOUSE_WHEEL
                    evt = MouseWheelEvent(120, x, y, x0, y0)
                elif e.button==5:
                    eventname = MOUSE_WHEEL
                    evt = MouseWheelEvent(-120, x, y, x0, y0)
                else:
                    eventname = MOUSE_BUTTON_UP
                    evt = MouseButtonEvent(e.button, x, y, x0, y0)
                eventmanager.event(eventname, evt)
            # MOUSEMOTION
            elif e.type==MOUSEMOTION:
                btns = 0
                b1,b2,b3 = e.buttons
                if b1:
                    btns |= 0x1
                if b2:
                    btns |= 0x2
                if b3:
                    btns |= 0x4                
                x,y = e.pos
                dx, dy = e.rel
                width = self.width
                height = self.height
                x0 = float(x)/width
                y0 = float(y)/height
                dx0 = float(dx)/width
                dy0 = float(dy)/height
                evt = MouseMoveEvent(x, y, dx, dy, x0, y0, dx0, dy0, btns)
                eventmanager.event(MOUSE_MOVE, evt)

    def createKeyDict(self):
        self.keydict = {
              8  : KEY_BACK,
              9  : KEY_TAB,
             13 : KEY_RETURN,
             27 : KEY_ESCAPE,
             32 : KEY_SPACE,
            276 : KEY_LEFT,
            273 : KEY_UP,
            275 : KEY_RIGHT,
            274 : KEY_DOWN,
            301 : KEY_CAPSLOCK,
            304 : KEY_SHIFT_LEFT,
            303 : KEY_SHIFT_RIGHT,
            306 : KEY_CONTROL_LEFT,
            305 : KEY_CONTROL_RIGHT,
            308 : KEY_ALT_LEFT,
            307 : KEY_ALT_RIGHT,
            310 : KEY_WINDOWS_LEFT,
            309 : KEY_WINDOWS_RIGHT,
            319 : KEY_WINDOWS_MENU,
            317 : KEY_PRINT,
            302 : KEY_SCROLL,
             19 : KEY_PAUSE,
            277 : KEY_INSERT,
            127 : KEY_DELETE,
            278 : KEY_HOME,
            279 : KEY_END,
            280 : KEY_PRIOR,
            281 : KEY_NEXT,
            282 : KEY_F1,
            283 : KEY_F2,
            284 : KEY_F3,
            285 : KEY_F4,
            286 : KEY_F5,
            287 : KEY_F6,
            288 : KEY_F7,
            289 : KEY_F8,
            290 : KEY_F9,
            291 : KEY_F10,
            292 : KEY_F11,
            293 : KEY_F12,
            300 : KEY_NUMLOCK,
            256 : KEY_NUMPAD0,
            257 : KEY_NUMPAD1,
            258 : KEY_NUMPAD2,
            259 : KEY_NUMPAD3,
            260 : KEY_NUMPAD4,
            261 : KEY_NUMPAD5,
            262 : KEY_NUMPAD6,
            263 : KEY_NUMPAD7,
            264 : KEY_NUMPAD8,
            265 : KEY_NUMPAD9,
            266 : KEY_NUMPAD_DECIMAL,
            267 : KEY_NUMPAD_DIVIDE,
            268 : KEY_NUMPAD_MULTIPLY,
            269 : KEY_NUMPAD_SUBTRACT,
            270 : KEY_NUMPAD_ADD,
            271 : KEY_NUMPAD_ENTER
            } 
    

