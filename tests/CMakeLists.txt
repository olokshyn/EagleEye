cmake_minimum_required(VERSION 3.10)
project(EagleEyeTests)

add_subdirectory(3rdparty/googletest)

include_directories(${gtest_SOURCE_DIR}/include)
include_directories(../lib)

file(GLOB TEST_SOURCES
        *.cpp)
add_executable(${PROJECT_NAME}
        ${TEST_SOURCES})
add_dependencies(${PROJECT_NAME} gtest_main)
target_link_libraries(${PROJECT_NAME} gtest_main EagleEyeLib)
