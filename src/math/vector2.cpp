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

#include "math/vector2.h"

/*!
 * @file
 *
 * @author Guillermo A. Amaral B. (gamaral) <g@maral.me>
 */

#if MARSHMALLOW_WITH_BOX2D
#   include <Box2D/Common/b2Math.h>
#endif

#include <cmath>

MARSHMALLOW_NAMESPACE_USE;
using namespace Math;

Vector2::Vector2(float ax, float ay)
    : Tuple2(ax, ay)
{
}

Vector2::Vector2(const Vector2 &c)
    : Tuple2(c)
{
}

Vector2
Vector2::normalized(void) const
{
	Vector2 n(*this);
	n.normalize();
	return(n);
}

Vector2 &
Vector2::normalize(void)
{
	const float m = magnitude();
	if (m != 0) {
		m_value[0] /= m;
		m_value[1] /= m;
	} else m_value[0] = m_value[1] = 0;

	return(*this);
}

float
Vector2::magnitude(void) const
{
	return(sqrtf(powf(m_value[0], 2)
	           + powf(m_value[1], 2)));
}

float
Vector2::magnitude2(void) const
{
	return(powf(m_value[0], 2)
	     + powf(m_value[1], 2));
}

float
Vector2::cross(const Vector2 &b) const
{
	return((x() * b.y()) - (y() * b.x()));
}

float
Vector2::dot(const Vector2 &b) const
{
	return((x() * b.x()) + (y() * b.y()));
}

#if MARSHMALLOW_WITH_BOX2D
Vector2::operator b2Vec2(void) const
{
	return(b2Vec2(m_value[0], m_value[1]));
}
#endif

