cmake_minimum_required(VERSION 3.10)
project(EagleEye)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-unused-variable")

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(cli)

include_directories(lib)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)

add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${PROJECT_NAME}Tests)
