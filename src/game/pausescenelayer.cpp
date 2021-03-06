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

#include "game/pausescenelayer.h"

/*!
 * @file
 *
 * @author Guillermo A. Amaral B. (gamaral) <g@maral.me>
 */

#include "math/point2.h"
#include "math/size2.h"
#include "graphics/painter.h"
#include "graphics/quadmesh.h"
#include "graphics/viewport.h"

MARSHMALLOW_NAMESPACE_USE;
using namespace Game;

const Core::Type PauseSceneLayer::sType("Game::PauseSceneLayer");

PauseSceneLayer::PauseSceneLayer(const Core::Identifier &i, IScene &s)
    : SceneLayerBase(i, s, slfUpdateBlock),
      m_mesh()
{
}

PauseSceneLayer::~PauseSceneLayer(void)
{
}

Graphics::SharedMesh
PauseSceneLayer::mesh(void) const
{
	return(m_mesh);
}

void
PauseSceneLayer::render(void)
{
	if (!m_mesh) {
		Math::Rect2 l_rect(Graphics::Viewport::Size());
		Graphics::QuadMesh *l_mesh = new Graphics::QuadMesh(l_rect);
		l_mesh->setColor(Graphics::Color(0.f, 0.f, 0.f, 0.6f));
		m_mesh = l_mesh;
	}

	Graphics::Painter::Draw(*m_mesh, Math::Point2(0,0));
}

const Core::Type &
PauseSceneLayer::Type(void)
{
	return(sType);
}

