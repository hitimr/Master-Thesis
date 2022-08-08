add_executable(precision precision.cu)


add_custom_target(
    run_precision
    COMMAND precision
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)