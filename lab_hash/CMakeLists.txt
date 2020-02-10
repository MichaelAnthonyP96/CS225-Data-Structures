add_executable(lab_hash
        tests/basic.cpp
        tests/catch.hpp
        tests/catchlib.h
        anagram_finder.cpp
        anagram_finder.h
        anagramtest.cpp
        char_counter.cpp
        char_counter.h
        charcount.cpp
        hashes.cpp
        hashes.h
        hashtable.h
        htiterator.cpp
        htiterator.h
        lfparse.cpp
        logfile_generator.cpp
        logfile_parser.cpp
        logfile_parser.h
        lphashtable.cpp
        lphashtable.h
        lpiterator.cpp
        lpiterator.h
        schashtable.cpp
        schashtable.h
        sciterator.cpp
        sciterator.h
        textfile.cpp
        textfile.h
        word_counter.cpp
        word_counter.h
        wordcount.cpp)

cmake_minimum_required(VERSION 3.15)
project(lab_hash)

# set project metadata ########################################################
set(HASH_MAJOR_VERSION 1)
set(HASH_MINOR_VERSION 0)
set(HASH_PATCH_VERSION 0)
set(HASH_EXTRA_VERSION "" CACHE STRING "Hash extra version string")
set(HASH_VERSION "${HASH_MAJOR_VERSION}.${HASH_MINOR_VERSION}")
set(HASH_VERSION
        "${HASH_VERSION}.${HASH_PATCH_VERSION}${HASH_EXTRA_VERSION}")
set(HASH_AUTHOR "Michael Pope (lead)")
set(HASH_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(HASH_DESCRIPTION "Exploring Hash Tables with three methods of collision resolution")
set(PROJECT_NAME "HASH version ${HASH_VERSION}")
project(${PROJECT_NAME} CXX)

# Set project defaults ########################################################
set(default_build_type "Release")
# creating code compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries." ON)
option(ENABLE_TESTS "Build with tests." ON)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" OFF)

# Setting compile and link options #############################################

# Adding flags to Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

# Compiled objects output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Turn on default warnings as errors for GNU compilers.
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wold-style-cast \
    #-Wnon-virtual-dtor -Wno-unused-parameter -Wno-invalid-offsetof")
endif()

mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

# set up RPATH
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_STANDARD 14)

include(GNUInstallDirs)

add_library(disjointSets
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/dsets.cpp)
target_include_directories(disjointSets
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>)

add_library(HASH
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/graph.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/graph_tools.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/lab_HASH_random.h)
target_include_directories(HASH
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/>)
target_link_libraries(HASH PUBLIC disjointSets)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

