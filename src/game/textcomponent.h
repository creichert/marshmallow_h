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

#ifndef GAME_TEXTCOMPONENT_H
#define GAME_TEXTCOMPONENT_H 1

#include "game/componentbase.h"

#include "core/string.h"
#include "core/weak.h"

#include "math/size2.h"

MARSHMALLOW_NAMESPACE_BEGIN

namespace Graphics
{
	struct ITileset;
	typedef Core::Shared<ITileset> SharedTileset;
}

namespace Game
{

	class PositionComponent;
	typedef Core::Weak<PositionComponent> WeakPositionComponent;

	/*! @brief Game Text Component Class */
	class GAME_EXPORT TextComponent : public ComponentBase
	{
		NO_ASSIGN(TextComponent);
		NO_COPY(TextComponent);

		Math::Size2f m_font_size;
		Graphics::SharedTileset m_tileset;
		Core::String m_text;
		int m_tile_offset;

	public:

		TextComponent(const Core::Identifier &i, IEntity &entity);
		virtual ~TextComponent(void);

		Math::Size2f & fontSize(void)
			{ return(m_font_size); }

		Graphics::SharedTileset & tileset(void)
			{ return(m_tileset); }

		Core::String & text(void)
			{ return(m_text); }

		int & tileOffset(void)
			{ return(m_tile_offset); }

	public: /* virtual */

		VIRTUAL const Core::Type & type(void) const
		    { return(Type()); }

		VIRTUAL void render(void);
		VIRTUAL void update(TIME d);

		VIRTUAL bool serialize(TinyXML::TiXmlElement &node) const;
		VIRTUAL bool deserialize(TinyXML::TiXmlElement &node);

	protected:

		void reset(void);

	public: /* static */

		static const Core::Type & Type(void);
	};
	typedef Core::Shared<TextComponent> SharedTextComponent;
	typedef Core::Weak<TextComponent> WeakTextComponent;
}

MARSHMALLOW_NAMESPACE_END

#endif
