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
  # BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} -j1
)

# build_subproject(
#   NAME openvdb
#   URL "https://github.com/AcademySoftwareFoundation/openvdb/archive/refs/tags/v9.1.0.zip"
#   CMAKE_RULE_MESSAGES
#     -D USE_BLOSC=ON
#     -D USE_ZLIB=ON
#     -D DOPENVDB_BUILD_NANOVDB=ON
# )

# ExternalProject_Add_StepDependencies(openvdb build tbb zlib blosc)


set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} PARENT_SCOPE)


