project(raytracing LANGUAGES C CXX CUDA)


# Packages
find_package(TBB REQUIRED)
find_package(OpenVDB REQUIRED)


# Libraries
rt_lib(
  NAME benchmarker
  SOURCES benchmarker/benchmarker.cpp
  HEADERS benchmarker/benchmarker.hpp
)

rt_lib(
  NAME rtmath
  SOURCES math/rt_math.cpp
  HEADERS math/rt_math.hpp
)

rt_lib(
  NAME logging
  HEADERS logging/logging.hpp
  SOURCES logging/logging.cpp
  DEPENDENCIES plog
)

# Executables
rt_exe(
  NAME precision
  SOURCES precision.cu
  DEPENDENCIES OpenVDB::openvdb rt::logging)

add_definitions(-DNANOVDB_USE_CUDA)