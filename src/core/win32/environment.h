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

/*!
 * @file
 *
 * @author Guillermo A. Amaral B. (gamaral) <g@maral.me>
 */

#pragma once

#ifndef CORE_ENVIRONMENT_H
#define CORE_ENVIRONMENT_H 1

#include <ctime>
#include <direct.h>
#include <stdint.h>
#include <windows.h>

/********************************************************************** types */

#define CHAR     char
#define INT16    int16_t
#define INT32    int32_t
#define INT64    int64_t
#define INT8     int8_t
#define TIME     float
#define TIME_MAX FLT_MAX
#define UID      uint32_t
#define UINT16   uint16_t
#define UINT32   uint32_t
#define UINT64   uint64_t
#define UINT8    uint8_t
#define WCHAR    wchar_t

/******************************************************************** defines */

#define CHDIR   _chdir
#define STRDUP  _strdup

/******************************************************************** exports */

#ifdef MARSHMALLOW_DLL
#   define DLL_EXPORT __declspec(dllexport)
#   define DLL_IMPORT __declspec(dllimport)
#else
#   define DLL_EXPORT
#   define DLL_IMPORT
#endif

#ifdef ENTRYPOINT_LIBRARY
#   define ENTRYPOINT_EXPORT DLL_EXPORT
#else
#   define ENTRYPOINT_EXPORT DLL_IMPORT
#endif

#ifdef CORE_LIBRARY
#   define CORE_EXPORT DLL_EXPORT
#else
#   define CORE_EXPORT DLL_IMPORT
#endif

#ifdef MATH_LIBRARY
#   define MATH_EXPORT DLL_EXPORT
#else
#   define MATH_EXPORT DLL_IMPORT
#endif

#ifdef EVENT_LIBRARY
#   define EVENT_EXPORT DLL_EXPORT
#else
#   define EVENT_EXPORT DLL_IMPORT
#endif

#ifdef GRAPHICS_LIBRARY
#   define GRAPHICS_EXPORT DLL_EXPORT
#else
#   define GRAPHICS_EXPORT DLL_IMPORT
#endif

#ifdef GAME_LIBRARY
#   define GAME_EXPORT DLL_EXPORT
#else
#   define GAME_EXPORT DLL_IMPORT
#endif

#ifdef EXTRA_LIBRARY
#   define EXTRA_EXPORT DLL_EXPORT
#else
#   define EXTRA_EXPORT DLL_IMPORT
#endif

#endif
