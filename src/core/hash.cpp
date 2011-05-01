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

#include "core/hash.h"

/*!
 * @file
 *
 * @author Guillermo A. Amaral B. (gamaral) <g@maral.me>
 */

MARSHMALLOW_NAMESPACE_USE;
using namespace Core;

Hash::Hash(void)
    : m_result(0)
{
}

Hash::Hash(const char *d, size_t length, UID mask)
    : m_result(Algorithm(d, length, mask))
{
}

Hash::Hash(const Hash &copy)
    : m_result(copy.m_result)
{
}

Hash::~Hash(void)
{
}

Hash &
Hash::operator=(const Marshmallow::Core::Hash &rhs)
{
	if (this != &rhs)
		m_result = rhs.m_result;
	return(*this);
}

UID
Hash::Algorithm(const char *data, size_t length, UID mask)
{
	if (!data) return(0);

	UID l_hash = 0;
	size_t l_i;

	for(l_i = 0; l_i < length; ++l_i) {
		l_hash += data[l_i];
		l_hash += (l_hash << 0x0A);
		l_hash ^= (l_hash >> 0x06);
	}

	l_hash += (l_hash << 0x03);
	l_hash ^= (l_hash >> 0x0B);
	l_hash += (l_hash << 0x0F);

	return(l_hash & mask);
}

void
Hash::rehash(const char *d, size_t length, UID mask)
{
	m_result = Algorithm(d, length, mask);
}

