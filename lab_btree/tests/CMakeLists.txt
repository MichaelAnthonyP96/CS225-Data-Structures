cmake_minimum_required(VERSION 3.1)

#include_directories(${PROJECT_SOURCE_DIR}/cs225/catch/)

set ( TEST_ENV_PATH_OPTIONS "PATH=${CMAKE_CURRENT_BINARY_DIR}/../bin:$ENV{PATH}")
#set ( TEST_ENV_LD_OPTIONS
#        "LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/lib:\
#${CMAKE_CURRENT_BINARY_DIR}/../lib")

# add subdir for the test results
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testResults)
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/expected
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${PROJECT_SOURCE_DIR}/Images
#        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Catch testing framework library
add_library(catch ${PROJECT_SOURCE_DIR}/cs225/catch/catchmain.cpp)
target_include_directories(catch
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/cs225/catch>)
set_target_properties(catch PROPERTIES LINKER_LANGUAGE CXX)

add_executable(runTests ${CMAKE_CURRENT_SOURCE_DIR}/basic.cpp)
target_link_libraries(runTests PUBLIC catch  bTree)
target_include_directories(runTests
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>)

add_executable(benchMarkTests ${CMAKE_CURRENT_SOURCE_DIR}/benchmark_test.cpp)
target_link_libraries(benchMarkTests PUBLIC catch bTree)
target_include_directories(benchMarkTests
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/Include>)

add_test(NAME allTests
        COMMAND ${PROJECT_BINARY_DIR}/bin/runTests
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME benchMark
        COMMAND ${PROJECT_BINARY_DIR}/bin/benchMarkTests
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

FILE(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/bin/results)

FILE(COPY ${PROJECT_SOURCE_DIR}/generate_plot.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
MESSAGE(STATUS "To generate the plot shown in the results, travel to the project build dir/bin"
        " and execute:\n ./dict_racer 64 200000 1000 true true true \n ./generate_plot.py results/*.csv")