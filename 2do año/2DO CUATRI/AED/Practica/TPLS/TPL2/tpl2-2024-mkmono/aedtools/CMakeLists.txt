## -*- mode: cmake -*-
cmake_minimum_required(VERSION 2.6)
if(($ENV{HOSTNAME} STREQUAL galileo) OR ($ENV{HOSTNAME} STREQUAL urubu))
  message("setting CMP0074 policy")
  cmake_policy(SET CMP0074 OLD)
endif()
project(aedtools)

## ================= BEGIN USER CONFIG =============================

## Optimized version
## set(CXXOPTFLAGS "-fopenmp -O2 -funroll-loops")

## Debug version
set(CXXOPTFLAGS "-fopenmp -O0 -g3") 
set(CMAKE_BUILD_TYPE "Debug")
## In the "library" version this is compiled just to use the
## tree and btree classes. Some tools like check_dni() and so
## on are not needed
add_compile_definitions(DO_LIBRARY_VERSION)
# if($ENV{HOSTNAME} STREQUAL galileo)
# endif()

## ================= END USER CONFIG=============================

set(BUILD_SHARED_LIBS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake-modules)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../aedtools.opt)

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -DHAVE_CONFIG_H ${CXXOPTFLAGS}")

add_library(aedtools util_btree.cpp util.cpp util_tree.cpp)

include_directories(
  BEFORE
  ${PROJECT_SOURCE_DIR}/..
)

install(TARGETS aedtools DESTINATION lib)
install(FILES btree.hpp tree.hpp util_btree.hpp util_tree.hpp util.hpp 
  DESTINATION include)
