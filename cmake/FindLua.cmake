# Locate Lua library
# This module defines
#  LUA_FOUND, if false, do not try to link to Lua 
#  LUA_LIBRARIES
#  LUA_INCLUDE_DIR, where to find lua.h 
#
# Note that the expected include convention is
#  #include "lua.h"
# and not
#  #include <lua/lua.h>
# This is because, the lua location is not standardized and may exist
# in locations other than lua/

#=============================================================================
# Copyright 2007-2009 Kitware, Inc.
# Copyright 2011 Marshmallow Engine.
# Copyright 2011 Guillermo A. Amaral B. (gamaral) <g@maral.me>
#=============================================================================
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

if(MARSHMALLOW_CONTRIB_LUA)
    set(LUA_FOUND ON)
    set(LUA_BASE "${PROJECT_SOURCE_DIR}/contrib/lua/code")
    set(LUA_INCLUDE_DIR ${LUA_BASE}/src/
                        ${LUA_BASE}/extra/)
    set(LUA_LIBRARY marshmallow_lua)
else()
    FIND_PATH(LUA_INCLUDE_DIR lua.h
      HINTS
      $ENV{LUA_DIR}
      PATH_SUFFIXES include/lua51 include/lua5.1 include/lua include
      PATHS
      ~/Library/Frameworks
      /Library/Frameworks
      /usr/local
      /usr
      /sw # Fink
      /opt/local # DarwinPorts
      /opt/csw # Blastwave
      /opt
    )

    FIND_LIBRARY(LUA_LIBRARY 
      NAMES lua51 lua5.1 lua-5.1 lua
      HINTS
      $ENV{LUA_DIR}
      PATH_SUFFIXES lib64 lib
      PATHS
      ~/Library/Frameworks
      /Library/Frameworks
      /usr/local
      /usr
      /sw
      /opt/local
      /opt/csw
      /opt
    )
endif()

IF(LUA_LIBRARY)
  # include the math library for Unix
  IF(UNIX AND NOT APPLE)
    FIND_LIBRARY(LUA_MATH_LIBRARY m)
    SET( LUA_LIBRARIES "${LUA_LIBRARY};${LUA_MATH_LIBRARY}" CACHE STRING "Lua Libraries")
  # For Windows and Mac, don't need to explicitly include the math library
  ELSE(UNIX AND NOT APPLE)
    SET( LUA_LIBRARIES "${LUA_LIBRARY}" CACHE STRING "Lua Libraries")
  ENDIF(UNIX AND NOT APPLE)
  SET(LUA_INCLUDE_DIRS ${LUA_INCLUDE_DIR} CACHE STRING "Lua Includes")
ENDIF(LUA_LIBRARY)

MARK_AS_ADVANCED(LUA_INCLUDE_DIR LUA_LIBRARIES LUA_LIBRARY LUA_MATH_LIBRARY)

