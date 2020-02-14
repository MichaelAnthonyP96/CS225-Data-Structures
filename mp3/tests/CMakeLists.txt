cmake_minimum_required(VERSION 3.1)

set ( TEST_ENV_PATH_OPTIONS "PATH=${CMAKE_CURRENT_BINARY_DIR}/../bin:$ENV{PATH}")
#set ( TEST_ENV_LD_OPTIONS
#        "LD_LIBRARY_PATH=${CMAKE_CURRENT_BINARY_DIR}/lib:\
#${CMAKE_CURRENT_BINARY_DIR}/../lib")

# add subdir for the result images
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/tests/Results)
file(COPY ${PROJECT_SOURCE_DIR}/tests/ExpectedImages DESTINATION ${PROJECT_BINARY_DIR}/tests/)
file(COPY ${PROJECT_SOURCE_DIR}/tests/alma.png DESTINATION ${PROJECT_BINARY_DIR}/tests/)
file(COPY ${PROJECT_SOURCE_DIR}/tests/merge1.png DESTINATION ${PROJECT_BINARY_DIR}/tests/)
file(COPY ${PROJECT_SOURCE_DIR}/tests/merge2.png DESTINATION ${PROJECT_BINARY_DIR}/tests/)
file(COPY ${PROJECT_SOURCE_DIR}/tests/split.png DESTINATION ${PROJECT_BINARY_DIR}/tests/)

# Catch testing framework library
add_library(catch ${CMAKE_SOURCE_DIR}/cs225/catch/catchmain.cpp)
target_include_directories(catch
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/cs225/catch/>)
set_target_properties(catch PROPERTIES LINKER_LANGUAGE CXX)

add_executable(runPart1
        ${CMAKE_CURRENT_SOURCE_DIR}/tests_part1.cpp)
target_link_libraries(runPart1 PUBLIC catch imageManipulation list)
target_include_directories(runPart1
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source/>)

add_executable(runPart2
        ${CMAKE_CURRENT_SOURCE_DIR}/tests_part2.cpp)
target_link_libraries(runPart2 PUBLIC catch imageManipulation list)
target_include_directories(runPart2
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source/>)

add_test(NAME part1
        COMMAND ${PROJECT_BINARY_DIR}/bin/runPart1
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/)
add_test(NAME part2
        COMMAND ${PROJECT_BINARY_DIR}/bin/runPart2
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/)
