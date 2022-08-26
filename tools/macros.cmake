## Copyright 2020 Jefferson Amstutz
## SPDX-License-Identifier: Unlicense

function(print)
  foreach(arg ${ARGN})
    message("${arg} = ${${arg}}")
  endforeach()
endfunction()

macro(setup_subproject_path_vars _NAME)
  set(SUBPROJECT_NAME ${_NAME})

  set(SUBPROJECT_INSTALL_PATH ${SUBPROJECT_NAME}/install)

  set(SUBPROJECT_SOURCE_PATH ${SUBPROJECT_NAME}/source)
  set(SUBPROJECT_STAMP_PATH ${SUBPROJECT_NAME}/stamp)
  set(SUBPROJECT_BUILD_PATH ${SUBPROJECT_NAME}/build)
endmacro()

macro(build_subproject)
  # See cmake_parse_arguments docs to see how args get parsed here:
  #    https://cmake.org/cmake/help/latest/command/cmake_parse_arguments.html
  set(oneValueArgs NAME URL)
  set(multiValueArgs DEPENDS_ON)
  cmake_parse_arguments(BUILD_SUBPROJECT "" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN})

  # Setup SUBPROJECT_* variables (containing paths) for this function
  set(SUBPROJECT_NAME ${BUILD_SUBPROJECT_NAME})

  # Build the actual subproject
  ExternalProject_Add(${SUBPROJECT_NAME}
    PREFIX ${SUBPROJECT_NAME}
    DOWNLOAD_DIR ${SUBPROJECT_NAME}/download
    STAMP_DIR ${SUBPROJECT_NAME}/stamp
    CONFIGURE_COMMAND ${SUBPROJECT_CONFIGURE_COMMAND}
    BINARY_DIR ${SUBPROJECT_NAME}/bin
    SOURCE_DIR ${SUBPROJECT_NAME}/src
    URL ${BUILD_SUBPROJECT_URL}
    CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
      -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT_NAME}
      -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}      
      -DCMAKE_CXX_FLAGS="-O2"
      -DCMAKE_CXX_FLAGS_DEBUG="-O0"

    BUILD_COMMAND ${DEFAULT_BUILD_COMMAND}
    BUILD_ALWAYS OFF
  )

  # Dependencies that must be installed before this component
  if(BUILD_SUBPROJECT_DEPENDS_ON)
    ExternalProject_Add_StepDependencies(${SUBPROJECT_NAME}
      build ${BUILD_SUBPROJECT_DEPENDS_ON}
    )
  endif()

  # Place installed component on CMAKE_PREFIX_PATH for downstream consumption
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT_NAME})
endmacro()


macro(rt_lib)
  # Parse Args
  set(oneValueArgs NAME)
  set(multiValueArgs SOURCES HEADERS DEPENDENCIES TEST_SOURCES PRECOMPILED_HEADERS)
  cmake_parse_arguments(RT_LIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Set Variables
  set(NAME ${RT_LIB_NAME})
  set(LIB_NAME lib${RT_LIB_NAME})
  set(TARGET ${LIB_NAME})

  # Library
  add_library(${TARGET} ${RT_LIB_SOURCES} ${RT_LIB_HEADERS})
  set_property(TARGET ${TARGET} PROPERTY OUTPUT_NAME ${NAME})
  add_library(rt::${NAME} ALIAS ${LIB_NAME})
  target_include_directories(${LIB_NAME} 
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR})

  # PCH
  target_precompile_headers(${TARGET} PUBLIC ${RT_LIB_HEADERS})

  # Link Dependencies
  if(RT_LIB_DEPENDENCIES)
    target_link_libraries(${TARGET} PUBLIC ${RT_LIB_DEPENDENCIES})
  endif()

  # Tests
  if(RT_LIB_TEST_SOURCES AND BUILD_TESTS)
    print(BUILD_TESTS)
    set(TEST_NAME ${NAME}_test)
    add_executable(${NAME}_test ${RT_LIB_TEST_SOURCES} ${RT_LIB_SOURCES})
    target_link_libraries(${NAME}_test GTest::gtest_main gmock) 
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
  endif()

endmacro()  

macro(rt_exe)
  # Parse args
  set(oneValueArgs NAME)
  set(multiValueArgs SOURCES HEADERS DEPENDENCIES)
  cmake_parse_arguments(RT_EXE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  set(TARGET ${RT_EXE_NAME})
  set(NAME ${RT_EXE_NAME})

  # Add executable and link libraries
  add_executable(${TARGET} ${RT_EXE_SOURCES} ${RT_EXE_HEADERS})
  target_include_directories(
    ${TARGET} 
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}
  )
  target_link_libraries(${TARGET} PUBLIC ${RT_EXE_DEPENDENCIES})



  # PCH
  target_precompile_headers(${TARGET} PUBLIC ${RT_EXE_HEADERS})

  # Command for invoking the program
  add_custom_target(
    run_${NAME}
    COMMAND ./${NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
  )
endmacro()


