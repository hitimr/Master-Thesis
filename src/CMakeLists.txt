# Packages
find_package(TBB REQUIRED)
find_package(OpenVDB REQUIRED)

# Benchmarker
add_library(libbenchmarker benchmarker/benchmarker.hpp
                           benchmarker/benchmarker.cpp)
set_property(TARGET libbenchmarker PROPERTY OUTPUT_NAME benchmarker)
add_library(rt::benchmarker ALIAS libbenchmarker)
target_include_directories(
  libbenchmarker PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(libbenchmarker)

# Main executable
add_executable(rt raytracing.cpp)
target_link_libraries(
  rt
  PUBLIC TBB::tbb OpenVDB::openvdb plog
  PRIVATE rt::benchmarker)

if(USE_PCH)
  target_precompile_headers(rt PUBLIC util/logging.hpp)
endif()

# Precision
add_executable(precision precision.cu)
target_link_libraries(precision PUBLIC OpenVDB::openvdb plog PRIVATE
                      rt::benchmarker)
                      
add_definitions(-DNANOVDB_USE_CUDA)



add_custom_target(
  run
  COMMAND precision
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})
