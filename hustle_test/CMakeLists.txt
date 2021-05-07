set(target_name "hustle_test")

set(src_files
    "src/erase.cpp")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name}
    compiler_features
    compiler_warnings
    hustle
    gmock_main)

set_target_properties(${target_name} PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER}/test)

gtest_discover_tests(${target_name})
