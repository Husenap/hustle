cmake_minimum_required(VERSION 3.16)

project("hustle" C CXX)

include("cmake/prevent_in_source_builds.cmake")
include("cmake/standard_project_setup.cmake")

include("cmake/compiler_features.cmake")
include("cmake/compiler_warnings.cmake")
include("cmake/auto_group_sources.cmake")

set(${PROJECT_NAME}_FOLDER
    ${PROJECT_NAME}
    CACHE STRING "The folder that ${PROJECT_NAME} projects will be placed in.")

option(${PROJECT_NAME}_BUILD_TESTS
    "If the ${PROJECT_NAME} tests are built in addition to the ${PROJECT_NAME} library."
    ON)

add_subdirectory("hustle")

if(${${PROJECT_NAME}_BUILD_TESTS})
    enable_testing()
    include(GoogleTest)
    include("thirdparty/googletest.cmake")
    add_subdirectory("hustle_test")
endif()
