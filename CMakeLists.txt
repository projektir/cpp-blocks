cmake_minimum_required(VERSION 3.9.3)

set(ProjectName cpp-blocks)

project(${ProjectName})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SourceFolder src)

add_executable(${ProjectName} ${SourceFolder}/main.cpp)
