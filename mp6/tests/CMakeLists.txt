cmake_minimum_required(VERSION 3.1)

set ( TEST_ENV_PATH_OPTIONS "PATH=${CMAKE_CURRENT_BINARY_DIR}/../bin:$ENV{PATH}")
#set ( TEST_ENV_LD_OPTIONS
#        "LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/lib:\
#${CMAKE_CURRENT_BINARY_DIR}/../lib")

# add subdir for the result images
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tests/Results)
file(COPY ${PROJECT_SOURCE_DIR}/tests/text.txt DESTINATION ${PROJECT_BINARY_DIR}/tests/)
file(COPY ${PROJECT_SOURCE_DIR}/tests/Solutions DESTINATION ${PROJECT_BINARY_DIR}/tests/)

# Catch testing framework library
add_library(catch ${CMAKE_CURRENT_SOURCE_DIR}/catch.hpp)
target_include_directories(catch
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>)
set_target_properties(catch PROPERTIES LINKER_LANGUAGE CXX)

add_executable(runTests ${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.cpp)
target_link_libraries(runTests PUBLIC catch )
target_include_directories(runTests
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}_DIR}/Include>)

add_test(NAME allTests
        COMMAND ${PROJECT_BINARY_DIR}/bin/runTests
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/tests)
