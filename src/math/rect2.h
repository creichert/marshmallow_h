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

#ifndef MATH_RECT2_H
#define MATH_RECT2_H 1

#include "core/global.h"
#include "math/size2.h"

MARSHMALLOW_NAMESPACE_BEGIN

namespace Math
{
	class Vector2;

	/*! @brief 2D Rect */
	class MATH_EXPORT Rect2
	{
		Size2f m_size;

	public:

		Rect2(float width, float height);
		explicit Rect2(const Size2f &size);
		Rect2(const Rect2 &copy);

		const Size2f & size(void) const
		    { return(m_size); }

		Vector2 topLeft(void) const;
		Vector2 topRight(void) const;
		Vector2 bottomLeft(void) const;
		Vector2 bottomRight(void) const;

		float area(void) const
		    { return(m_size.area()); }

	public: /* operators */

		Rect2 & operator=(const Rect2 &rhs)
		    { m_size = rhs.m_size;
		      return(*this); }
	};
}

MARSHMALLOW_NAMESPACE_END

#endif
