add_subdirectory(plog)

build_subproject(
  NAME blosc
  URL "https://github.com/Blosc/c-blosc/archive/refs/tags/v1.21.1.zip"
)

build_subproject(
  NAME zlib
  URL "http://zlib.net/fossils/zlib-1.2.12.tar.gz"
)

build_subproject(
  NAME TBB
  URL "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.zip"
)


ExternalProject_Add(openvdb
  URL "https://github.com/AcademySoftwareFoundation/openvdb/archive/refs/tags/v9.1.0.zip"
  DOWNLOAD_DIR openvdb/download
  PREFIX openvdb
  CMAKE_ARGS
    -D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -D CMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -D CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -D CMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/openvdb
    -D CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
    -D TBB_ROOT=${CMAKE_BINARY_DIR}/external/TBB/
    -D CMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/openvdb
    -D OPENVDB_BUILD_NANOVDB=ON
    -D NANOVDB_USE_CUDA=${NANOVDB_USE_CUDA}
    -D USE_TBB=ON
  BUILD_ALWAYS OFF
  BUILD_COMMAND ${DEFAULT_BUILD_COMMAND}
)

ExternalProject_Add_StepDependencies(openvdb build TBB zlib blosc)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR}/openvdb/lib/cmake/OpenVDB)

# Every subdirectoy has its own Variable scope
# We need to propagate the current CMAKE_PREFIX_PATH upwards so it can be found the the project
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} PARENT_SCOPE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)


