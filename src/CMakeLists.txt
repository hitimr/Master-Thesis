add_executable(rt raytracing.cpp)

print(CMAKE_PREFIX_PATH)

find_package(TBB REQUIRED)
target_link_libraries(rt 
    PUBLIC 
        TBB::tbb
        plog)

