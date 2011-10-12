/*
 * Copyright 2011 Marshmallow Engine. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this list of
 *      conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice, this list
 *      of conditions and the following disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY MARSHMALLOW ENGINE ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MARSHMALLOW ENGINE OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Marshmallow Engine.
 */

#include "qtglwindow.h"

/*!
 * @file
 *
 * @author Christopher Reichert creichert07@gmail.com
 */

#include <QtOpenGL/QGLWidget>
#include <QtGui/QPainter>
#include <QtGui/QKeyEvent>

#include <QtCore/QDebug>

#include "core/logger.h"
#include "event/keyboardevent.h"
#include "event/eventmanager.h"

MARSHMALLOW_NAMESPACE_USE;


QtGLWindow::QtGLWindow(QWidget* parent)
	: QGLWidget(parent)
{
}

QtGLWindow::QtGLWindow(QGLContext* context, QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f)
	: QGLWidget(context, parent, shareWidget, f)
{
}

QtGLWindow::~QtGLWindow()
{
}

void
QtGLWindow::paintGL()
{
}

void
QtGLWindow::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
}

void
QtGLWindow::initializeGL()
{
	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glClearColor(.0f, .0f, .0f, .0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void
QtGLWindow::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.end();
}

void
QtGLWindow::keyReleaseEvent(QKeyEvent* event)
{
	keyPressEvent(event);
}

void
QtGLWindow::keyPressEvent(QKeyEvent* event)
{
	typedef eastl::list<Event::KBKeys> KeyList;
	static KeyList s_keys_pressed;

	Event::KBKeys l_key = Event::KEY_NONE;
	Event::KBActions l_action =
	    (event->type() == QEvent::KeyPress ?
	                      Event::KeyPressed : Event::KeyReleased);

	switch (event->key()) {
	case Qt::Key_0:            l_key = Event::KEY_0; break;
	case Qt::Key_1:            l_key = Event::KEY_1; break;
	case Qt::Key_2:            l_key = Event::KEY_2; break;
	case Qt::Key_3:            l_key = Event::KEY_3; break;
	case Qt::Key_4:            l_key = Event::KEY_4; break;
	case Qt::Key_5:            l_key = Event::KEY_5; break;
	case Qt::Key_6:            l_key = Event::KEY_6; break;
	case Qt::Key_7:            l_key = Event::KEY_7; break;
	case Qt::Key_8:            l_key = Event::KEY_8; break;
	case Qt::Key_9:            l_key = Event::KEY_9; break;
	case Qt::Key_A:            l_key = Event::KEY_A; break;
	case Qt::Key_B:            l_key = Event::KEY_B; break;
	case Qt::Key_C:            l_key = Event::KEY_C; break;
	case Qt::Key_D:            l_key = Event::KEY_D; break;
	case Qt::Key_E:            l_key = Event::KEY_E; break;
	case Qt::Key_F:            l_key = Event::KEY_F; break;
	case Qt::Key_G:            l_key = Event::KEY_G; break;
	case Qt::Key_H:            l_key = Event::KEY_H; break;
	case Qt::Key_I:            l_key = Event::KEY_I; break;
	case Qt::Key_J:            l_key = Event::KEY_J; break;
	case Qt::Key_K:            l_key = Event::KEY_K; break;
	case Qt::Key_L:            l_key = Event::KEY_L; break;
	case Qt::Key_M:            l_key = Event::KEY_M; break;
	case Qt::Key_N:            l_key = Event::KEY_N; break;
	case Qt::Key_O:            l_key = Event::KEY_O; break;
	case Qt::Key_P:            l_key = Event::KEY_P; break;
	case Qt::Key_Q:            l_key = Event::KEY_Q; break;
	case Qt::Key_R:            l_key = Event::KEY_R; break;
	case Qt::Key_S:            l_key = Event::KEY_S; break;
	case Qt::Key_T:            l_key = Event::KEY_T; break;
	case Qt::Key_U:            l_key = Event::KEY_U; break;
	case Qt::Key_V:            l_key = Event::KEY_V; break;
	case Qt::Key_W:            l_key = Event::KEY_W; break;
	case Qt::Key_X:            l_key = Event::KEY_X; break;
	case Qt::Key_Y:            l_key = Event::KEY_Y; break;
	case Qt::Key_Z:            l_key = Event::KEY_Z; break;
	case Qt::Key_Alt:          l_key = Event::KEY_ALT_L; break;
	case Qt::Key_Backspace:    l_key = Event::KEY_BACKSPACE; break;
	case Qt::Key_CapsLock:     l_key = Event::KEY_CAPS_LOCK; break;
	case Qt::Key_Clear:        l_key = Event::KEY_CLEAR; break;
	case Qt::Key_Control:      l_key = Event::KEY_CONTROL_L; break;
	case Qt::Key_Delete:       l_key = Event::KEY_DELETE; break;
	case Qt::Key_Down:         l_key = Event::KEY_DOWN; break;
	case Qt::Key_End:          l_key = Event::KEY_END; break;
	case Qt::Key_Escape:       l_key = Event::KEY_ESCAPE; break;
	case Qt::Key_Help:         l_key = Event::KEY_HELP; break;
	case Qt::Key_Home:         l_key = Event::KEY_HOME; break;
	case Qt::Key_Insert:       l_key = Event::KEY_INSERT; break;
	case Qt::Key_Left:         l_key = Event::KEY_LEFT; break;
	case Qt::Key_Menu:         l_key = Event::KEY_MENU; break;
	case Qt::Key_Meta:         l_key = Event::KEY_META_L; break;
	case Qt::Key_NumLock:      l_key = Event::KEY_NUM_LOCK; break;
	case Qt::Key_PageDown:     l_key = Event::KEY_PAGE_DOWN; break;
	case Qt::Key_PageUp:       l_key = Event::KEY_PAGE_UP; break;
	case Qt::Key_Pause:        l_key = Event::KEY_PAUSE; break;
	case Qt::Key_Print:        l_key = Event::KEY_PRINT; break;
	case Qt::Key_Return:       l_key = Event::KEY_RETURN; break;
	case Qt::Key_Right:        l_key = Event::KEY_RIGHT; break;
	case Qt::Key_ScrollLock:   l_key = Event::KEY_SCROLL_LOCK; break;
	case Qt::Key_Shift:        l_key = Event::KEY_SHIFT_L; break;
	case Qt::Key_Tab:          l_key = Event::KEY_TAB; break;
	case Qt::Key_Up:           l_key = Event::KEY_UP; break;
	case Qt::Key_Backslash:    l_key = Event::KEY_BACKSLASH; break;
	case Qt::Key_BracketLeft:  l_key = Event::KEY_BRACKETLEFT; break;
	case Qt::Key_BracketRight: l_key = Event::KEY_BRACKETRIGHT; break;
	case Qt::Key_Equal:        l_key = Event::KEY_EQUAL; break;
	case Qt::Key_Less:         l_key = Event::KEY_LESS; break;
	case Qt::Key_QuoteDbl:     l_key = Event::KEY_DBLQUOTE; break;
	case Qt::Key_Semicolon:    l_key = Event::KEY_SEMICOLON; break;
	case Qt::Key_Space:        l_key = Event::KEY_SPACE; break;
	case Qt::Key_F1:           l_key = Event::KEY_F1; break;
	case Qt::Key_F2:           l_key = Event::KEY_F2; break;
	case Qt::Key_F3:           l_key = Event::KEY_F3; break;
	case Qt::Key_F4:           l_key = Event::KEY_F4; break;
	case Qt::Key_F5:           l_key = Event::KEY_F5; break;
	case Qt::Key_F6:           l_key = Event::KEY_F6; break;
	case Qt::Key_F7:           l_key = Event::KEY_F7; break;
	case Qt::Key_F8:           l_key = Event::KEY_F8; break;
	case Qt::Key_F9:           l_key = Event::KEY_F9; break;
	case Qt::Key_F10:          l_key = Event::KEY_F10; break;
	case Qt::Key_F11:          l_key = Event::KEY_F11; break;
	case Qt::Key_F12:          l_key = Event::KEY_F12; break;
	case Qt::Key_F13:          l_key = Event::KEY_F13; break;
	case Qt::Key_F14:          l_key = Event::KEY_F14; break;
	case Qt::Key_F15:          l_key = Event::KEY_F15; break;
/*
	case XK_KP_0:         l_key = Event::KEY_K0; break;
	case XK_KP_1:         l_key = Event::KEY_K1; break;
	case XK_KP_2:         l_key = Event::KEY_K2; break;
	case XK_KP_3:         l_key = Event::KEY_K3; break;
	case XK_KP_4:         l_key = Event::KEY_K4; break;
	case XK_KP_5:         l_key = Event::KEY_K5; break;
	case XK_KP_6:         l_key = Event::KEY_K6; break;
	case XK_KP_7:         l_key = Event::KEY_K7; break;
	case XK_KP_8:         l_key = Event::KEY_K8; break;
	case XK_KP_9:         l_key = Event::KEY_K9; break;
	case XK_KP_Decimal:   l_key = Event::KEY_KDECIMAL; break;
	case XK_KP_Divide:    l_key = Event::KEY_KDIVIDE; break;
	case XK_KP_Multiply:  l_key = Event::KEY_KMULTIPLY; break;
*/
	default: MMWARNING1("Unknown key pressed!");
	}

	bool l_key_pressed = false;
	KeyList::const_iterator l_pressed_key_i;
	for (l_pressed_key_i = s_keys_pressed.begin();
	     l_pressed_key_i != s_keys_pressed.end();
	     ++l_pressed_key_i)
		if (*l_pressed_key_i == l_key) {
			l_key_pressed = true;
			break;
		}

	if (( l_key_pressed && l_action != Event::KeyPressed)
	 || (!l_key_pressed && l_action == Event::KeyPressed)) {
		Event::SharedEvent event(new Event::KeyboardEvent(l_key, l_action));
		Event::EventManager::Instance()->queue(event);

		if (l_key_pressed) s_keys_pressed.remove(l_key);
		else s_keys_pressed.push_front(l_key);
	}
}
