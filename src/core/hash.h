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

#ifndef CORE_HASH_H
#define CORE_HASH_H 1

#include "core/environment.h"
#include "core/namespace.h"

MARSHMALLOW_NAMESPACE_BEGIN

namespace Core
{

	/*! @brief Hash Class */
	class CORE_EXPORT Hash
	{
		UID   m_result;

	public:

		/*! @brief Hash Contructor */
		Hash(void);

		/*!
		 * @brief Hash Contructor
		 * @param d Data to hash
		 * @param length Data length
		 * @param mask UID mask
		 */
		Hash(const char *d, size_t length, UID mask);

		/*!
		 * @brief Hash Copy Contructor
		 * @param copy Hash
		 */
		Hash(const Hash &copy);
		virtual ~Hash(void);

		/*! @brief Datum */
		UID result(void) const
		    { return(m_result); }

	public: /* operator */

		operator UID() const
		    { return(m_result); }

		Marshmallow::Core::Hash & operator=(const Marshmallow::Core::Hash &rhs);

		bool operator==(const Hash &rhs) const
		    { return(m_result == rhs.m_result); }

		bool operator!=(const Hash &rhs) const
		    { return(m_result != rhs.m_result); }

		bool operator<(const Hash &rhs) const
		    { return(m_result < rhs.m_result); }

	public: /* static */

		/*! @brief One-at-a-Time Hash */
		static UID Algorithm(const char *data, size_t length, UID mask);

	protected:

		void rehash(const char *d, size_t length, UID mask);
	};

}

MARSHMALLOW_NAMESPACE_END

#endif
