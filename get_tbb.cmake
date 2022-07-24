## Copyright 2020 Jefferson Amstutz
## SPDX-License-Identifier: Unlicense

set(SUBPROJECT_NAME tbb)
set(SUBPROJECT_DIR external/${SUBPROJECT_NAME})


set(TBB_URL https://github.com/oneapi-src/oneTBB/releases/download/v2021.5.0/oneapi-tbb-2021.5.0-lin.tgz)
set(TBB_LIB_PATH "/lib/intel64/gcc4.8")
set(TBB_LIB_DESTINATION "lib")

ExternalProject_Add(tbb
  PREFIX ${SUBPROJECT_DIR}
  STAMP_DIR ${SUBPROJECT_DIR}/stamp
  SOURCE_DIR ${SUBPROJECT_DIR}/unpacked
  BINARY_DIR ""
  URL ${TBB_URL}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND "${CMAKE_COMMAND}" -E copy_directory
    <SOURCE_DIR>/${TBB_LIB_PATH}
    ${INSTALL_DIR_ABSOLUTE}/${TBB_LIB_DESTINATION}
  BUILD_ALWAYS OFF
)

append_cmake_prefix_path("${CMAKE_BINARY_DIR}/${SUBPROJECT_DIR}/unpacked/")

set(TBB_TARGET tbb)
