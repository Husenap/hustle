set(target_name "hustle_test")

set(src_algorithm
    "src/algorithm/erase.cpp")

set(src_memory
    "src/memory/allocator.cpp")

set(src_files
    ${src_algorithm}
    ${src_memory})

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name}
    compiler_features
    compiler_warnings
    hustle
    gmock_main)

auto_group_sources(src_files ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${target_name} PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER}/test)

gtest_discover_tests(${target_name})
