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

#ifndef GAME_ANIMATIONCOMPONENT_H
#define GAME_ANIMATIONCOMPONENT_H 1

#include "game/componentbase.h"

#include <EASTL/map.h>
#include <EASTL/vector.h>

#include "core/weak.h"

MARSHMALLOW_NAMESPACE_BEGIN

namespace Graphics
{
	struct ITextureCoordinateData;
	typedef Core::Shared<ITextureCoordinateData> SharedTextureCoordinateData;
}

namespace Game
{

	class RenderComponent;
	typedef Core::Weak<RenderComponent> WeakRenderComponent;

	class TilesetComponent;
	typedef Core::Weak<TilesetComponent> WeakTilesetComponent;

	struct GAME_EXPORT AnimationSequence;

	/*! @brief Game Animation Component Class */
	class GAME_EXPORT AnimationComponent : public ComponentBase
	{
		NO_ASSIGN(AnimationComponent);
		NO_COPY(AnimationComponent);

		typedef eastl::pair<int, int> FrameEntry;
		typedef eastl::vector<FrameEntry> FrameList;
		typedef eastl::map<Core::Identifier, FrameList> AnimationFrames;
		typedef eastl::map<Core::Identifier, float> AnimationFramerates;
		AnimationFrames     m_animation_frames;
		AnimationFramerates m_animation_framerate;
		Graphics::SharedTextureCoordinateData m_stop_data;

		WeakRenderComponent  m_render;
		WeakTilesetComponent m_tileset;

		TIME m_timestamp;
		bool m_loop;
		bool m_playing;

		const FrameList *m_current_framelist;
		float m_current_framerate;
		int   m_current_frame_duration;
		unsigned int m_current_frame_entries;
		unsigned int m_current_frame_entry;

	public:

		AnimationComponent(const Core::Identifier &identifier, IEntity &entity);
		virtual ~AnimationComponent(void);

		void pushFrame(const Core::Identifier &animation, int tile, int duration = 1);
		void popFrame(const Core::Identifier &animation);
		void rate(const Core::Identifier &animation, float fps);

		void play(const Core::Identifier &animation, bool loop = false);
		void stop(int *tile = 0);

	public: /* virtual */

		VIRTUAL const Core::Type & type(void) const
		    { return(Type()); }

		VIRTUAL void update(TIME d);

		VIRTUAL bool serialize(TinyXML::TiXmlElement &node) const;
		VIRTUAL bool deserialize(TinyXML::TiXmlElement &node);

	public: /* static */

		static const Core::Type & Type(void);
	};
	typedef Core::Shared<AnimationComponent> SharedAnimationComponent;
	typedef Core::Weak<AnimationComponent> WeakAnimationComponent;
}

MARSHMALLOW_NAMESPACE_END

#endif
