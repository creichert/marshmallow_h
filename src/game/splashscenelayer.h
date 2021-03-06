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

#pragma once

/*!
 * @file
 *
 * @author Guillermo A. Amaral B. (gamaral) <g@maral.me>
 */

#ifndef GAME_SPLASHSCENELAYER_H
#define GAME_SPLASHSCENELAYER_H 1

#include "game/scenelayerbase.h"
#include "event/ieventlistener.h"

#include "EASTL/list.h"
using namespace eastl;

#include "core/identifier.h"
#include "core/shared.h"
#include "core/type.h"

MARSHMALLOW_NAMESPACE_BEGIN

namespace Graphics
{
	class QuadMesh;
	typedef Core::Shared<QuadMesh> SharedQuadMesh;
}

namespace Game
{

	/*! @brief Game Splash Scene Layer Class */
	class GAME_EXPORT SplashSceneLayer : public SceneLayerBase
	                                   , public Event::IEventListener
	{
		NO_ASSIGN(SplashSceneLayer);
		NO_COPY(SplashSceneLayer);

		enum SplashState
		{
			ssInit     = 0,
			ssFadeIn   = 1,
			ssExposure = 2,
			ssFadeOut  = 3,
			ssFinished = 4
		};

		Graphics::SharedQuadMesh m_mesh;
		Event::SharedEventListener m_event_proxy;
		TIME m_exposure;
		TIME m_fade;
		TIME m_timer;
		SplashState m_state;
		bool m_autoBegin;
		bool m_autoKill;

	public:

		SplashSceneLayer(const Core::Identifier &identifier,
		    IScene &scene);
		virtual ~SplashSceneLayer(void);

		Graphics::SharedQuadMesh mesh(void) const;

		TIME exposure(void) const
		    { return(m_exposure); }
		void setExposure(TIME t)
		    { m_exposure = t; }

		TIME fade(void) const
		    { return(m_fade); }
		void setFade(TIME t)
		    { m_fade = t; }

		bool autoKill(void) const
		    { return(m_autoKill); }
		void setAutoKill(bool ak)
		    { m_autoKill = ak; }

		void reset(void);
		bool skip(void);

	public: /* virtual */

		VIRTUAL const Core::Type & type(void) const
		    { return(Type()); }

		VIRTUAL void render(void);
		VIRTUAL void update(TIME delta);

		VIRTUAL bool serialize(TinyXML::TiXmlElement &node) const;
		VIRTUAL bool deserialize(TinyXML::TiXmlElement &node);

		VIRTUAL bool handleEvent(const Event::IEvent &event);

	public: /* static */

		static const Core::Type & Type(void);

	protected:

		void setState(SplashState state);

	private: /* static */

		static const Core::Type sType;
	};
	typedef Core::Shared<SplashSceneLayer> SharedSplashSceneLayer;
	typedef Core::Weak<SplashSceneLayer> WeakSplashSceneLayer;

}

MARSHMALLOW_NAMESPACE_END

#endif
