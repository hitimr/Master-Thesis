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

# CMake 
include(ExternalProject)
include(GNUInstallDirs)
include(ProcessorCount)

include(tools/macros.cmake)



# Options
ProcessorCount(PROCESSOR_COUNT)
set(NUM_BUILD_JOBS ${PROCESSOR_COUNT} CACHE STRING "Number of build jobs '-j <n>'")
set(DEFAULT_BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} -j ${NUM_BUILD_JOBS})
# set(DEFAULT_BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} -j2)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(external)
add_subdirectory(src)
