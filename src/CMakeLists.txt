project(raytracing LANGUAGES C CXX CUDA)


# Packages
find_package(TBB REQUIRED)
find_package(OpenVDB REQUIRED)
find_package(plog REQUIRED)
find_package(DataFrame REQUIRED)

# Add current Dir to System Path so they can e included with <folder/module.hpp>
include_directories(BEFORE SYSTEM ${CMAKE_CURRENT_SOURCE_DIR})


if(BUILD_TESTS)
  find_package(GTest REQUIRED)
  enable_testing()
  include(GoogleTest)
endif()


# Libraries
rt_lib(
  NAME benchmarker
  SOURCES benchmarker/benchmarker.cpp
  HEADERS benchmarker/benchmarker.hpp
)

rt_lib(
  NAME logging
  HEADERS logging/logging.hpp
  SOURCES logging/logging.cpp
  DEPENDENCIES plog::plog
)

rt_lib(
  NAME math
  SOURCES math/math.cpp
  HEADERS math/math.hpp
  TEST_SOURCES math/math.test.cpp
)

# add_definitions(-DNANOVDB_USE_CUDA)
add_subdirectory(experiments)