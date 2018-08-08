cmake_minimum_required(VERSION 3.10)
project(EagleEyeLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB LIB_SOURCES
        *.cpp
        *.hpp
        parsers/*.cpp
        parsers/*.hpp
        actions/*.cpp
        actions/*.hpp)
add_library(${PROJECT_NAME} ${LIB_SOURCES})
