add_executable(rt raytracing.cpp)


find_package(TBB REQUIRED)
find_package(OpenVDB REQUIRED)


target_link_libraries(rt 
    PUBLIC 
        TBB::tbb
        OpenVDB::openvdb
        plog
    )

add_subdirectory(experiments)