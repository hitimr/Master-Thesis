build_subproject(
  NAME blosc
  URL "https://github.com/Blosc/c-blosc/archive/refs/tags/v1.21.1.zip"
)

build_subproject(
  NAME zlib
  URL "http://zlib.net/fossils/zlib-1.2.12.tar.gz"
)

build_subproject(
  NAME tbb
  URL "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.zip"
  # BUILD_COMMAND cmake --build . --config ${CMAKE_BUILD_TYPE} -j1
)


