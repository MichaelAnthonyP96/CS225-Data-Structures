cmake_minimum_required(VERSION 3.1)

#include_directories(${PROJECT_SOURCE_DIR}/cs225/catch/)

set ( TEST_ENV_PATH_OPTIONS "PATH=${CMAKE_CURRENT_BINARY_DIR}/../bin:$ENV{PATH}")
#set ( TEST_ENV_LD_OPTIONS
#        "LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/lib:\
#${CMAKE_CURRENT_BINARY_DIR}/../lib")

# add subdir for the test results
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testResults)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/expected
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/Images
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Catch testing framework library
add_library(catch ${PROJECT_SOURCE_DIR}/cs225/catch/catchmain.cpp)
target_include_directories(catch
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/cs225/catch/>)

add_executable(runPart1 ${CMAKE_CURRENT_SOURCE_DIR}/tests_part1.cpp)
target_link_libraries(runPart1 PUBLIC mp5 util catch imageManipulation)
target_include_directories(runPart1
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/tests>)

add_executable(runPart2 ${CMAKE_CURRENT_SOURCE_DIR}/tests_part2.cpp)
target_link_libraries(runPart2 mp5 util catch imageManipulation)
target_include_directories(runPart2
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/tests>)

add_test(NAME TestP1
        COMMAND ${PROJECT_BINARY_DIR}/bin/runPart1
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME TestP2
        COMMAND ${PROJECT_BINARY_DIR}/bin/runPart2
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})