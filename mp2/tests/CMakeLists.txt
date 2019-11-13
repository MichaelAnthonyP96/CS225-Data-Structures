cmake_minimum_required(VERSION 3.1)

include_directories(${PROJECT_SOURCE_DIR}/cs225/catch/)

add_executable(runPart1 part1.cpp)
add_executable(runPart2 part2.cpp)

target_link_libraries(runPart1 mp2 catch imageManipulation)
target_link_libraries(runPart2 mp2 catch imageManipulation)

add_test(NAME TestP1
        COMMAND ${CMAKE_COMMAND}
        runPart1
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})