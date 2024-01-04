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

set(MainFile "src/main.cpp")

add_library(${This} STATIC ${Sources} ${Headers})

add_executable(main ${MainFile})

add_subdirectory(test)