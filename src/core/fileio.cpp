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

#include "core/fileio.h"

/*!
 * @file
 *
 * @author Guillermo A. Amaral B. (gamaral) <g@maral.me>
 */

MARSHMALLOW_NAMESPACE_USE;
using namespace Core;

Identifier m_filename;
FILE      *m_handle;

FileIO::FileIO(void)
    : m_filename()
    , m_handle(0)
{
}

FileIO::FileIO(const Identifier &fn, DIOMode m)
    : m_filename()
    , m_handle(0)
{
	open(fn, m);
}

FileIO::~FileIO(void)
{
	close();
}

bool
FileIO::open(const Identifier &fn, DIOMode m)
{
	char l_mode[4] = {0, 0, 0, 0};
	unsigned char l_mode_c = 0;

	if (m && DIOReadOnly)
		l_mode[l_mode_c++] = 'r';
	if (m && DIOWriteOnly)
		l_mode[l_mode_c++] = 'w';
	if (m && DIOBinary)
		l_mode[l_mode_c++] = 'b';
	
	m_handle = fopen(fn, l_mode);
	return(m_handle != 0);
}

void
FileIO::close(void)
{
	fclose(m_handle);
	m_handle = 0;
	m_filename = Identifier();
}

bool
FileIO::isOpen(void) const
{
	return(m_handle != 0);
}

size_t
FileIO::read(char *b, size_t bs)
{
	return(fread(b, bs, 1, m_handle));
}

size_t
FileIO::write(const char *b, size_t bs)
{
	return(fwrite(b, bs, 1, m_handle));
}

bool
FileIO::seek(long int o, DIOSeek on)
{
	int l_origin;

	switch (on) {
	case   DIOStart: l_origin = SEEK_SET; break;
	case     DIOEnd: l_origin = SEEK_END; break;
	case DIOCurrent: l_origin = SEEK_CUR; break;
	default: return(false);
	}

	return(fseek(m_handle, o, l_origin) == 0);
}

long int
FileIO::tell(void) const
{
	return(ftell(m_handle));
}

long int
FileIO::size(void) const
{
	const long int l_cursor = ftell(m_handle);
	long int l_result = -1;

	fseek(m_handle, 0, SEEK_END);
	l_result = ftell(m_handle);
	fseek(m_handle, l_cursor, SEEK_SET);

	return(l_result);
}

