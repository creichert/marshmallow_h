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

find_package(Lua)
include_directories(${LUA_INCLUDE_DIRS})

file(GLOB LUA_SRCS ${LUA_BASE}/src/lapi.c
                   ${LUA_BASE}/src/lauxlib.c
                   ${LUA_BASE}/src/lbaselib.c
                   ${LUA_BASE}/src/lcode.c
                   ${LUA_BASE}/src/ldblib.c
                   ${LUA_BASE}/src/ldebug.c
                   ${LUA_BASE}/src/ldo.c
                   ${LUA_BASE}/src/ldump.c
                   ${LUA_BASE}/src/lfunc.c
                   ${LUA_BASE}/src/lgc.c
                   ${LUA_BASE}/src/linit.c
                   ${LUA_BASE}/src/liolib.c
                   ${LUA_BASE}/src/llex.c
                   ${LUA_BASE}/src/lmathlib.c
                   ${LUA_BASE}/src/lmem.c
                   ${LUA_BASE}/src/loadlib.c
                   ${LUA_BASE}/src/lobject.c
                   ${LUA_BASE}/src/lopcodes.c
                   ${LUA_BASE}/src/loslib.c
                   ${LUA_BASE}/src/lparser.c
                   ${LUA_BASE}/src/lstate.c
                   ${LUA_BASE}/src/lstring.c
                   ${LUA_BASE}/src/lstrlib.c
                   ${LUA_BASE}/src/ltable.c
                   ${LUA_BASE}/src/ltablib.c
                   ${LUA_BASE}/src/ltm.c
                   ${LUA_BASE}/src/lundump.c
                   ${LUA_BASE}/src/lvm.c
                   ${LUA_BASE}/src/lzio.c
                   ${LUA_BASE}/src/print.c
)


if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
	if (BUILD_SHARED_LIBS)
		set(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")
		set(CMAKE_C_FLAGS "-fPIC ${CMAKE_C_FLAGS}")
	endif()
endif()

add_library(${LUA_LIBRARY} ${LUA_SRCS})

