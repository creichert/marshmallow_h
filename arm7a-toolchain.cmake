# Cross-compilation setup for arm7a-omap3.
#
# This file is passed to cmake on the command line via
# -DCMAKE_TOOLCHAIN_FILE.  It gets read first, prior to any of cmake's
# system tests.
#
# Make sure to add any library directory paths in your environment to
# CMAKE_FIND_ROOT_PATH
#
# Example: If you have a cross compile toolchain you need to add the
# system root using something similar to:
#       -DTARGET_SYSTEM_ROOT=/path/to/system/root
#
# If you are cross compiling any libraries that are not part of your
# system root you will need to add these too.
#
#       -DQT_EMBEDDED_DIR=/path/to/qt-embedded

set(TARGET_SYSTEM_ROOT "" CACHE STRING "System root when cross-compiling.")
set(QT_EMBEDDED_DIR "" CACHE STRING "Cross compiled qt-embedded libraries.")
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER arm-angstrom-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER arm-angstrom-linux-gnueabi-g++)

# ideally user will be able to set cmake flag here for their root directory
set(CMAKE_FIND_ROOT_PATH ${SYSTEM_ROOT}
                         ${QT_EMBEDDED_DIR})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

