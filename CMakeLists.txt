# Original CMakeLists.txt file by:
## Copyright 2020 Jefferson Amstutz
## SPDX-License-Identifier: Unlicense

cmake_minimum_required(VERSION 3.16)


if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX
      "${CMAKE_BINARY_DIR}/install"
      CACHE STRING "Final install location." FORCE)
endif()


# CMake Modules
include(ExternalProject)
include(GNUInstallDirs)
include(ProcessorCount)
include(CheckLanguage)

# Custom CMake Stuff
include(tools/macros.cmake)

# CUDA Stuff
# find_package(FindCUDAToolkit)

# Options
ProcessorCount(PROCESSOR_COUNT)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(NUM_BUILD_JOBS ${PROCESSOR_COUNT} CACHE STRING "Number of build jobs '-j <n>'")
set(DEFAULT_BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} -j ${NUM_BUILD_JOBS})

# Compile Flags
set(CMAKE_CXX_FLAGS "-O3 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall")
set(CMAKE_CUDA_FLAGS "-O3 -g -Wall")
set(CMAKE_CUDA_FLAGS_DEBUG "-O0 -g -Wall")

# Versions, Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(MINIMUM_BOOST_VERSION 1.63.0)

project(raytracing)

# Subfolders
add_subdirectory(external)
add_subdirectory(src)
