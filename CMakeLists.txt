cmake_minimum_required(VERSION 3.10)
project(EagleEye)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-unused-variable")

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(cli)

include_directories(lib)

add_dependencies(${PROJECT_NAME}Tests ${PROJECT_NAME}Lib)
add_dependencies(${PROJECT_NAME}CLI ${PROJECT_NAME}Lib)

add_custom_target(Tests
        ${PROJECT_NAME}Tests
        DEPENDS ${PROJECT_NAME}Lib
        DEPENDS ${PROJECT_NAME}Tests)

add_custom_target(EagleEye
        mv cli/${PROJECT_NAME}CLI ${PROJECT_NAME}
        DEPENDS ${PROJECT_NAME}CLI
        DEPENDS Tests)
