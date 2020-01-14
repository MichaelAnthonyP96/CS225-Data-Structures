cmake_minimum_required(VERSION 3.15)
project(lab_puzzles)

# set project metadata ########################################################
set(PUZZLES_MAJOR_VERSION 1)
set(PUZZLES_MINOR_VERSION 0)
set(PUZZLES_PATCH_VERSION 0)
set(PUZZLES_EXTRA_VERSION "" CACHE STRING "Puzzles extra version string")
set(PUZZLES_VERSION "${PUZZLES_MAJOR_VERSION}.${PUZZLES_MINOR_VERSION}")
set(PUZZLES_VERSION
        "${PUZZLES_VERSION}.${PUZZLES_PATCH_VERSION}${PUZZLES_EXTRA_VERSION}")
set(PUZZLES_AUTHOR "Michael Pope (lead)")
set(PUZZLES_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(PUZZLES_DESCRIPTION "Word processing using and investigating dictionaries")
set(PROJECT_NAME "PUZZLES version ${PUZZLES_VERSION}")
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

add_library(wordProcessing
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/anagram_dict.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/cartalk_puzzle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/common_words.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/fib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/homophone_puzzle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/pronounce_dict.cpp
        )
target_include_directories(wordProcessing
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/>)
set_target_properties(wordProcessing PROPERTIES LINKER_LANGUAGE CXX)

add_executable(anagramFinder
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/anagram_finder.cpp)
target_link_libraries(anagramFinder PUBLIC wordProcessing)
target_include_directories(anagramFinder
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)

add_executable(factorialCalc
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/fac.cpp)
target_include_directories(factorialCalc
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)

add_executable(fibGen
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/fib_generator.cpp)
target_link_libraries(fibGen PUBLIC wordProcessing)
target_include_directories(fibGen
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)

add_executable(findCommonWords
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/find_common_words.cpp)
target_link_libraries(findCommonWords PUBLIC wordProcessing)
target_include_directories(findCommonWords
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Export HEAPS as a CMake package
#install(FILES Lab_HeapsConfig.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HEAPS)
#install(EXPORT HEAPS
#        NAMESPACE HEAPS::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HEAPS)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/PUZZLES.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/PUZZLES.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_puzzles)
endif()