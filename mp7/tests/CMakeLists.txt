cmake_minimum_required(VERSION 3.1)

set ( TEST_ENV_PATH_OPTIONS "PATH=${CMAKE_CURRENT_BINARY_DIR}/../bin:$ENV{PATH}")
#set ( TEST_ENV_LD_OPTIONS
#        "LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/lib:\
#${CMAKE_CURRENT_BINARY_DIR}/../lib")

# add subdir for the result images
#file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tests/Results)
file(GLOB test_images "${PROJECT_SOURCE_DIR}/tests/*.png")
file(COPY ${test_images} DESTINATION ${PROJECT_BINARY_DIR}/tests/)

# Catch testing framework library
add_library(catch ${PROJECT_SOURCE_DIR}/cs225/catch/catchmain.cpp)
target_include_directories(catch
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/cs225/catch/>)
set_target_properties(catch PROPERTIES LINKER_LANGUAGE CXX)

add_executable(runTestsPart1 ${CMAKE_CURRENT_SOURCE_DIR}/test_part1.cpp)
target_link_libraries(runTestsPart1 PUBLIC catch imageManipulation disjointSets maze mazeReader)
target_include_directories(runTestsPart1
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}_DIR}/Include>)

add_executable(runTestsPart2 ${CMAKE_CURRENT_SOURCE_DIR}/test_part2.cpp)
target_link_libraries(runTestsPart2 PUBLIC catch imageManipulation disjointSets maze mazeReader)
target_include_directories(runTestsPart2
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>)

add_executable(runTestDsets ${CMAKE_CURRENT_SOURCE_DIR}/testdsets.cpp)
target_link_libraries(runTestDsets PUBLIC catch imageManipulation disjointSets maze mazeReader)
target_include_directories(runTestDsets
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>)

add_executable(runSquareMazeTest ${CMAKE_CURRENT_SOURCE_DIR}/testsquaremaze.cpp)
target_link_libraries(runSquareMazeTest PUBLIC catch imageManipulation disjointSets maze mazeReader)
target_include_directories(runSquareMazeTest
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>)

add_test(NAME part1Tests
        COMMAND ${PROJECT_BINARY_DIR}/bin/runTestsPart1
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

add_test(NAME part2Tests
        COMMAND ${PROJECT_BINARY_DIR}/bin/runTestsPart2
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

add_test(NAME destsTests
        COMMAND ${PROJECT_BINARY_DIR}/bin/runTestDsets
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

add_test(NAME squareMazeTest
        COMMAND ${PROJECT_BINARY_DIR}/bin/runSquareMazeTest
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests)
