cmake_minimum_required(VERSION 3.15)
project(mp2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cs225)
include_directories(cs225/catch)
include_directories(cs225/lodepng)

# Catch testing framework library
add_library(catch cs225/catch/catchmain.cpp)
target_include_directories(catch PUBLIC
        $<BUILD_INTERFACE:/cs225/catch/>)

add_library(imageManipulation
        cs225/HSLAPixel.cpp
        cs225/lodepng/lodepng.cpp
        cs225/PNG.cpp)
target_include_directories(imageManipulation PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cs225/>)

add_library(mp2
        #tests/part1.cpp
        #tests/part2.cpp
        Image.cpp
        Image.h
        #main.cpp
        #mp2-1.cpp
        StickerSheet.cpp
        StickerSheet.h)
target_include_directories(mp2 PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

add_executable(main main.cpp)
target_link_libraries(main mp2 imageManipulation catch)

enable_testing()
add_subdirectory(tests)

#add_executable(test1 tests/part1.cpp)
#add_executable(test2 tests/part2.cpp)

#target_link_libraries(test1 mp2)
#target_link_libraries(test2 mp2)