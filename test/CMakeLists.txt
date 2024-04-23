cmake_minimum_required(VERSION 3.15)

set(This wad_testing)

file(GLOB SOURCES
    "*.cpp"
)

add_executable(${This} ${SOURCES})
target_link_libraries(${This} PUBLIC
    gtest_main
    wad
)

target_include_directories(${This} PUBLIC ../src)

add_test(
    NAME ${This}
    COMMAND ${This}
)
