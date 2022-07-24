add_executable(rt raytracing.cpp)

find_package(TBB REQUIRED)
target_link_libraries(rt PUBLIC TBB::tbb)