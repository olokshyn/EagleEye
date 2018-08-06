cmake_minimum_required(VERSION 3.10)
project(EagleEye)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)

file(GLOB LIB_SOURCES
        lib/*.cpp
        lib/*.hpp
        lib/parsers/*.cpp
        lib/parsers/*.hpp)
add_library(${PROJECT_NAME}Lib ${LIB_SOURCES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)