# Original CMakeLists.txt file by:
## Copyright 2020 Jefferson Amstutz
## SPDX-License-Identifier: Unlicense

cmake_minimum_required(VERSION 3.16)


if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX
      "${CMAKE_BINARY_DIR}/install"
      CACHE STRING "Final install location." FORCE)
endif()

project(raytracing)

include(ExternalProject)
include(GNUInstallDirs)
include(ProcessorCount)

include(macros.cmake)

# Options ##

ProcessorCount(PROCESSOR_COUNT)
set(NUM_BUILD_JOBS ${PROCESSOR_COUNT} CACHE STRING "Number of build jobs '-j <n>'")
set(DEFAULT_BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} -j ${NUM_BUILD_JOBS})

option(DOWNLOAD_TBB "Download TBB, otherwise rely on system" ON)

## Build OSPRay dependencies ##

# get_filename_component(INSTALL_DIR_ABSOLUTE
#   ${CMAKE_BINARY_DIR}/local_deps ABSOLUTE BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})

if (DOWNLOAD_TBB)
  include(get_tbb.cmake)
endif()

add_subdirectory(src)
add_subdirectory(external)
