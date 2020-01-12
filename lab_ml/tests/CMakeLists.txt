cmake_minimum_required(VERSION 3.1)

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
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/cs225/catch/>)

add_executable(runTests ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.cpp)
target_link_libraries(runTests PUBLIC ML catch imageManipulation)
target_include_directories(runTests
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/cs225/catch)

add_test(NAME allTests
        COMMAND ${PROJECT_BINARY_DIR}/bin/runTests
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})