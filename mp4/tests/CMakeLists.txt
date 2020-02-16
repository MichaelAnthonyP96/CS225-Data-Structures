cmake_minimum_required(VERSION 3.1)

set ( TEST_ENV_PATH_OPTIONS "PATH=${CMAKE_CURRENT_BINARY_DIR}/../bin:$ENV{PATH}")
#set ( TEST_ENV_LD_OPTIONS
#        "LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/lib:\
#${CMAKE_CURRENT_BINARY_DIR}/../lib")

# add subdir for the result images
#file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tests/Results)
#file(COPY ${PROJECT_SOURCE_DIR}/tests/text.txt DESTINATION ${PROJECT_BINARY_DIR}/tests/)
#file(COPY ${PROJECT_SOURCE_DIR}/tests/Solutions DESTINATION ${PROJECT_BINARY_DIR}/tests/)

#[[add_executable(mp4
        cs225/catch/catch.hpp
        cs225/catch/catchmain.cpp
        tests/catch.hpp
        tests/testmain.cpp
        tests/tests_part1.cpp
        tests/tests_part2.cpp)]]

# Catch testing framework library
add_library(catch ${CMAKE_CURRENT_SOURCE_DIR}/testmain.cpp)
target_include_directories(catch
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
set_target_properties(catch PROPERTIES LINKER_LANGUAGE CXX)

add_executable(runTestsPart1 ${CMAKE_CURRENT_SOURCE_DIR}/tests_part1.cpp)
target_link_libraries(runTestsPart1 PUBLIC catch imageManipulation Point traversals colorPicker animation)
target_include_directories(runTestsPart1
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}_DIR}/Include>)

add_executable(runTestsPart2 ${CMAKE_CURRENT_SOURCE_DIR}/tests_part2.cpp)
target_link_libraries(runTestsPart2 PUBLIC catch imageManipulation Point traversals colorPicker animation)
target_include_directories(runTestsPart2
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}_DIR}/Include>)

add_test(NAME part1Tests
        COMMAND ${PROJECT_BINARY_DIR}/bin/runTestsPart1
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

add_test(NAME part2Tests
        COMMAND ${PROJECT_BINARY_DIR}/bin/runTestsPart2
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests)
