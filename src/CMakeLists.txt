project(raytracing LANGUAGES C CXX CUDA)


# Packages
find_package(TBB REQUIRED)
find_package(OpenVDB REQUIRED)

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

# Executables
rt_exe(
  NAME precision
  SOURCES precision.cu
  DEPENDENCIES OpenVDB::openvdb rt::logging rt::math
  )

add_definitions(-DNANOVDB_USE_CUDA)