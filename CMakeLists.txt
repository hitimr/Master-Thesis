Cmake_minimum_required(VERSION 3.16)


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
include(tools/UseLATEX.cmake)

# Options
option(USE_PCH "Use precompiled headers" ON)
option(DISABLE_CUDA "Enable CUDA Components. Can be turned off to work on devices without a GPU" OFF)
option(NANOVDB_USE_CUDA "Enable CUDA + GPU for NanoVDB" ON)

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_DEPENDENCIES "Build all dependencies" ON)
option(BUILD_DEPENDENCY_OPENVDB "Build OpenVDB." ON)
option(BUILD_RT_PROJECT "Build the main project" OFF)
option(BUILD_VDB_VIEW "Build vdb_view" OFF)
option(BUILD_PYOPENVDB "Build OpenVDB Python BIndings" OFF)
option(CMAKE_BUILD_TYPE Debug)


# Definitions
ProcessorCount(PROCESSOR_COUNT)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(PROJECT_EXTERNAL_DIR ${PROJECT_ROOT_DIR}/external)
set(NUM_BUILD_JOBS ${PROCESSOR_COUNT} CACHE STRING "Number of build jobs '-j <n>'")
set(DEFAULT_BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} -j ${NUM_BUILD_JOBS})

# Compile Flags
set(CMAKE_CXX_FLAGS "-O3 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall")

# Versions, Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MINIMUM_BOOST_VERSION 1.63.0)

# CUDA specific stuff
if(DSIABLE_CUDA)
  set(CUDA_LANG "")
else()
  set(CUDA_LANG "CUDA")
  enable_language(CUDA)
  set(CMAKE_CUDA_STANDARD 17)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)
  set(CMAKE_CUDA_FLAGS "-O3")
  set(CMAKE_CUDA_FLAGS_DEBUG "-O0 -g")
endif()

project(raytracing LANGUAGES C CXX ${CUDA_LANG})

# Subfolders
add_subdirectory(external)
add_subdirectory(doc)

if(BUILD_RT_PROJECT)
  add_subdirectory(src)
endif()
