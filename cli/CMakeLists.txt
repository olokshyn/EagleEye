cmake_minimum_required(VERSION 3.10)
project(EagleEyeCLI)

include_directories(../lib)
include_directories(3rdparty/tclap/include)

file(GLOB CLI_SOURCES
        *.cpp
        *.hpp)

add_executable(${PROJECT_NAME} ${CLI_SOURCES})
target_link_libraries(${PROJECT_NAME} EagleEyeLib)
