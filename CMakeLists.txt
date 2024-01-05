cmake_minimum_required(VERSION 3.15)

set (This wad)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(vendor/googletest)

file(GLOB Headers
    "src/wad/*.hpp"
)

file(GLOB Sources
    "src/wad/*.cpp"
)

set(wadFile "doom1.wad")
set(MainFile "src/main.cpp")
configure_file(${wadFile} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
add_library(${This} STATIC ${Sources} ${Headers})

add_executable(examples ${MainFile})

add_subdirectory(test)
configure_file(${wadFile} ${CMAKE_CURRENT_BINARY_DIR}/test COPYONLY)