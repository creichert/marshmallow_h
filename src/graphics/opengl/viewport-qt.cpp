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

#include <QtGui/QApplication>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLContext>
#include <QtOpenGL/QGLFormat>
#include <QtCore/QDebug>

#include "graphics/viewport.h"
#include "qtglwindow.h"

/*!
 * @file
 *
 * @author Christopher Reichert creichert07@gmail.com
 */

#ifdef Q_WS_X11
#include <QtGui/QX11Info>
#include <X11/X.h>
#define XMD_H
#include <X11/XKBlib.h>
#include <X11/extensions/xf86vmode.h>
#endif

#include <EASTL/list.h>

#include "core/logger.h"

#include "event/quitevent.h"

#include "graphics/painter.h"

MARSHMALLOW_NAMESPACE_USE;
using namespace Graphics;

/******************************************************************************/

namespace
{
	struct ViewportData {
		QApplication *app;
		QtGLWindow   *window;
		QGLFormat    *format;
		QGLContext   *context;
		Math::Size2i  wsize;
		int           screen;
		Math::Triplet camera;
		Math::Size2f  size;
		Math::Point2  visible[2];
		bool          fullscreen;
		bool          loaded;
		bool          vbo_supported;
	} s_data;

	bool CheckVBOSupport(void);
	void UpdateViewport(void);
	void HandleKeyEvent(QKeyEvent &key);

	void InitializeViewport(void)
	{
		s_data.camera[0] = s_data.camera[1] = .0f; // camera x y
		s_data.camera[2] = 1.f;                    // camera zoom
		s_data.context = 0;
		s_data.fullscreen = false;
		s_data.loaded = false;
		s_data.screen = 0;
		s_data.size.zero();
		s_data.vbo_supported = false;
		s_data.visible[0] = s_data.visible[1] = Math::Point2::Zero();
		s_data.window = 0;
		s_data.wsize[0] = s_data.wsize[1] = 0;
	}

	bool
	CreateWindow(int w, int h, int d, bool f)
	{
		s_data.context   = 0;
		s_data.loaded    = false;
		s_data.screen    = 0;
		s_data.window    = 0;

		s_data.fullscreen = f;
		s_data.wsize[0] = w;
		s_data.wsize[1] = h;

		/* create context */
		s_data.format = new QGLFormat;
		s_data.context = new QGLContext(*s_data.format);
		s_data.window = new QtGLWindow(s_data.context);

		/* initialize context */
		UpdateViewport();

		if(glGetError() != GL_NO_ERROR) {
			MMERROR1("Qt failed during initialization.");
			return(false);
		}
		s_data.window->show();
		return(s_data.loaded = true);
	}

	void
	DestroyWindow(void)
	{
		s_data.loaded = false;
		s_data.screen = 0;

		delete s_data.context; s_data.context = 0;
		delete s_data.window; s_data.window = 0;
		delete s_data.app; s_data.app = 0;
	}

	bool
	IsExtensionSupported(const char *list, const char *extension)
	{
		return(false);
	}

	bool
	CheckVBOSupport(void)
	{
		return(false);
	}

	void
	UpdateViewport(void)
	{
        s_data.size[0] = DEFAULT_VIEWPORT_VWIDTH * s_data.camera[2];
		s_data.size[1] = DEFAULT_VIEWPORT_VHEIGHT * s_data.camera[2];

		const float l_hw = s_data.size[0] / 2.f;
		const float l_hh = s_data.size[1] / 2.f;

		/* update visible area */
		s_data.visible[0][0] = -l_hw + s_data.camera[0];
		s_data.visible[0][1] =  l_hh + s_data.camera[1];
		s_data.visible[1][0] =  l_hw + s_data.camera[0];
		s_data.visible[1][1] = -l_hh + s_data.camera[1];

#ifdef Q_WS_X11
		/* update projection */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(s_data.visible[0].x(), s_data.visible[1].x(),
		        s_data.visible[1].y(), s_data.visible[0].y(), -1.f, 1.f);
		glMatrixMode(GL_MODELVIEW);
#endif // Q_WS_X11

	}

} // namespace

/******************************************************************************/

bool
Viewport::Initialize(int w, int h, int d, bool f)
{
    InitializeViewport();
	int argc = 0;
	char** argv = 0;
	s_data.app = new QApplication(argc, argv, QApplication::GuiServer);
	if (!CreateWindow(w, h, d, f)) {
		DestroyWindow();
		return(false);
	}

	Painter::Initialize();
	return(true);
}

void
Viewport::Finalize(void)
{
	Painter::Finalize();
	DestroyWindow();
}

bool
Viewport::Redisplay(int w, int h, int d, bool f)
{
	DestroyWindow();
	QCoreApplication::processEvents();
	if(!CreateWindow(w, h, d, f)) {
		DestroyWindow();
		return(false);
	}
	return(true);
}

void
Viewport::Tick(TIME t)
{
	QCoreApplication::processEvents(QEventLoop::AllEvents);
}

void
Viewport::SwapBuffer(void)
{
	s_data.window->swapBuffers();
	glClearColor(.0f, .0f, .0f, .0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glLoadIdentity();
}

const Math::Triplet &
Viewport::Camera(void)
{
	return(s_data.camera);
}

void
Viewport::MoveCamera(const Math::Triplet &c)
{
	s_data.camera[0] = c[0];
	s_data.camera[1] = c[1];
	s_data.camera[2] = c[2];
	UpdateViewport();
}

void
Viewport::VisibleArea(Math::Point2 *tl, Math::Point2 *br)
{
	if (tl) *tl = s_data.visible[0];
	if (br) *br = s_data.visible[1];
}

const Math::Size2f &
Viewport::Size(void)
{
	return(s_data.size);
}

const Math::Size2i &
Viewport::WindowSize(void)
{
	return(s_data.wsize);
}

const Core::Type &
Viewport::Type(void)
{
	static const Core::Type s_type("QT");
	return(s_type);
}

