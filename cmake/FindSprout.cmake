# - Find Sprout C++ library
# Once done this will define
#
#  SPROUT_INCLUDE_DIRS   - where to find sprout/darkroom.hpp
#  SPROUT_FOUND          - True if Sprout found.
#
#
#=============================================================================
# Copyright 2013 Naomasa Matsubayashi
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

set(_SPROUT_SEARCHES)

# Search SPROUT_ROOT first if it is set.
if(SPROUT_ROOT)
  set(_SPROUT_SEARCH_ROOT PATHS ${SPROUT_ROOT} NO_DEFAULT_PATH)
  list(APPEND _SPROUT_SEARCHES _SPROUT_SEARCH_ROOT)
endif()

# Normal search.
set(_SPROUT_SEARCH_NORMAL
  PATHS "[HKEY_LOCAL_MACHINE\\SOFTWARE\\GnuWin32\\Zlib;InstallPath]"
        "$ENV{PROGRAMFILES}/zlib"
        "/usr"
        "/usr/local"
        "/opt/sprout"
  )
list(APPEND _SPROUT_SEARCHES _SPROUT_SEARCH_NORMAL)

# Try each search configuration.
foreach(search ${_SPROUT_SEARCHES})
  find_path(SPROUT_INCLUDE_DIR NAMES sprout/darkroom.hpp ${${search}} PATH_SUFFIXES include)
endforeach()

mark_as_advanced(SPROUT_INCLUDE_DIR)

# handle the QUIETLY and REQUIRED arguments and set SPROUT_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS( SPROUT REQUIRED_VARS SPROUT_INCLUDE_DIR )

if(SPROUT_FOUND)
    set(SPROUT_INCLUDE_DIRS ${SPROUT_INCLUDE_DIR})
endif()

