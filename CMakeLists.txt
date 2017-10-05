cmake_minimum_required(VERSION 3.9.3)

set(ProjectName cpp-blocks)

project(${ProjectName})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(VendorDir "C:/Projects/${ProjectName}/Vendor")

# SDL2
set(SDL2Dir "${VendorDir}/SDL2")
set(SDL2LibraryDirs "${SDL2Dir}/lib/x64")
set(SDL2IncludeDirs "${SDL2Dir}/include")
set(SDL2Libraries "${SDL2LibraryDirs}/SDL2.lib;${SDL2LibraryDirs}/SDL2main.lib")

# SDL2_image
set(SDL2ImageDir "${VendorDir}/SDL2_image")
set(DSL2ImageLibraryDirs "${SDL2ImageDir}/lib/x64")
set(SDL2ImageIncludeDirs "${SDL2ImageDir}/include")
set(SDL2ImageLibraries "${DSL2ImageLibraryDirs}/SDL2_image.lib")

include_directories(${ProjectName} ${SDL2IncludeDirs})
include_directories(${ProjectName} ${SDL2ImageIncludeDirs})

set(SourceFolder src)

add_executable(${ProjectName} ${SourceFolder}/main.cpp)

target_link_libraries(${ProjectName} ${SDL2Libraries})
target_link_libraries(${ProjectName} ${SDL2ImageLibraries})
