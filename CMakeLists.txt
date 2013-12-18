cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeFiles/modules/")

project(sprout)
ENABLE_TESTING()

include(CheckIncludeFiles)
include (FindPkgConfig)
include(CheckCXXSourceCompiles)

# build type
set(CMAKE_BUILD_TYPE Debug)


set(CMAKE_CXX_FLAGS_DEBUG "-W -Wall -Wextra -Wno-unused-parameter -Werror -std=c++0x -O0 -g")
set(CMAKE_C_FLAGS_DEBUG "-W -Wall -Wextra -Wno-unused-parameter -Werror -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-W -Wall -Wextra -Wno-unused-parameter -Werror -std=c++0x -O2")
set(CMAKE_C_FLAGS_RELEASE "-W -Wall -Wextra -Wno-unused-parameter -Werror -O2")

#if you don't want the full compiler output, remove the following line
if( NOT DEFINED CMAKE_VERBOSE_MAKEFILE )
  set(CMAKE_VERBOSE_MAKEFILE OFF)
endif( NOT DEFINED CMAKE_VERBOSE_MAKEFILE )

if( NOT DEFINED Boost_USE_MULTITHREADED )
  set(Boost_USE_MULTITHREADED ON)
endif( NOT DEFINED Boost_USE_MULTITHREADED )

find_package( Boost 1.49.0 REQUIRED )
if( NOT Boost_FOUND )
  message( SEND_ERROR "Required package Boost was not detected." )
endif (NOT Boost_FOUND)

pkg_check_modules(OpenCV opencv)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS} )
link_directories( ${Boost_LIBRARY_DIRS} )
subdirs( sprout libs tools cmake )

