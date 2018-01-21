CMAKE_MINIMUM_REQUIRED(VERSION 3.6.0)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

SET(ProjectName cpp-blocks)

PROJECT(${ProjectName})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W3")

SET(SourceFolder src)

set(SDL2PP_WITH_IMAGE ON)
ADD_SUBDIRECTORY(extlib/libSDL2pp)

INCLUDE_DIRECTORIES(${SDL2PP_INCLUDE_DIRS})

ADD_EXECUTABLE(${ProjectName} ${SourceFolder}/main.cpp
    ${SourceFolder}/game.hpp ${SourceFolder}/game.cpp
    ${SourceFolder}/figure.hpp ${SourceFolder}/figure.cpp
    ${SourceFolder}/figure_variant.hpp ${SourceFolder}/figure_variant.cpp
    ${SourceFolder}/utils.hpp ${SourceFolder}/utils.cpp)

TARGET_LINK_LIBRARIES(${ProjectName} ${SDL2PP_LIBRARIES})
