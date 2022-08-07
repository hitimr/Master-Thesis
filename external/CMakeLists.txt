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
  PREFIX openvdb
  DOWNLOAD_DIR openvdb/download
  STAMP_DIR openvdb/stamp
  SOURCE_DIR openvdb/src
  BINARY_DIR openvdb/bin
  URL "https://github.com/AcademySoftwareFoundation/openvdb/archive/refs/tags/v9.1.0.zip"
  CMAKE_ARGS
    -D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -D CMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    -D CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -D CMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT_NAME}
    -D CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
    -D TBB_ROOT=${CMAKE_BINARY_DIR}/external/TBB/include
  BUILD_ALWAYS OFF
  BUILD_COMMAND ${DEFAULT_BUILD_COMMAND}
)

ExternalProject_Add_StepDependencies(openvdb build TBB zlib blosc)

# Every subdirectoy has its own Variable scope
# We need to propagate the current CMAKE_PREFIX_PATH upwards so it can be found the the project
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} PARENT_SCOPE)


