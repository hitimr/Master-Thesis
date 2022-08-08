# Directories
add_subdirectory(experiments)

# Packages
find_package(TBB REQUIRED)
find_package(OpenVDB REQUIRED)


add_executable(rt raytracing.cpp)

target_link_libraries(rt 
    PUBLIC 
        TBB::tbb
        OpenVDB::openvdb
        plog
    )

