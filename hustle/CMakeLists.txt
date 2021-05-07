set(target_name "hustle")

set(src_hustle
    "src/hustle/erase.inl"
    "src/hustle/algorithm.hpp")

set(src_files
    ${src_hustle})

# Project
add_library(${target_name} INTERFACE)
add_custom_target(${target_name}_ SOURCES ${src_files})
target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

source_group("src" FILES ${src_hustle})

set_target_properties(${target_name}_ PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER})
