# Copyright 2011 Marshmallow Engine. All rights reserved.
# Copyright 2011 Guillermo A. Amaral B. (gamaral) <g@maral.me>
#
# Redistribution and use in source and binary forms, with or without modification, are
# permitted provided that the following conditions are met:
#
#    1. Redistributions of source code must retain the above copyright notice, this list of
#       conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above copyright notice, this list
#       of conditions and the following disclaimer in the documentation and/or other materials
#       provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY MARSHMALLOW ENGINE ``AS IS'' AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
# FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MARSHMALLOW ENGINE OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# The views and conclusions contained in the software and documentation are those of the
# authors and should not be interpreted as representing official policies, either expressed
# or implied, of Marshmallow Engine.
#
#=============================================================================
#
#  EASTL_DEFINITIONS
#  EASTL_INCLUDE_DIRS
#  EASTL_LIBRARIES
#
#=============================================================================

if(NOT DEFINED EASTL_LIBRARIES)
	set(EASTL_BASE "${PROJECT_SOURCE_DIR}/contrib/eastl/code" CACHE STRING "")
	set(EASTL_INCLUDE_DIR ${EASTL_BASE}/include CACHE STRING "")
	set(EASTL_LIBRARY marshmallow_eastl CACHE STRING "")

	set(EASTL_INCLUDE_DIRS ${EASTL_INCLUDE_DIR} CACHE STRING "")
	set(EASTL_LIBRARIES ${EASTL_LIBRARY} CACHE STRING "")

	mark_as_advanced(EASTL_BASE EASTL_INCLUDE_DIR EASTL_LIBRARY EASTL_INCLUDE_DIRS EASTL_LIBRARIES)

	message(STATUS "EASTL from ${EASTL_BASE}")
endif()

if(BUILD_SHARED_LIBS)
	set(EASTL_DEFINITIONS "-DEASTL_DLL=1")
endif()

include_directories(${EASTL_INCLUDE_DIRS})
add_definitions(${EASTL_DEFINITIONS})

