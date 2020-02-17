cmake_minimum_required(VERSION 3.15)

# set project metadata ########################################################
set(MP7_MAJOR_VERSION 1)
set(MP7_MINOR_VERSION 0)
set(MP7_PATCH_VERSION 0)
set(MP7_EXTRA_VERSION "" CACHE STRING "MP7 extra version string")
set(MP7_VERSION "${MP7_MAJOR_VERSION}.${MP7_MINOR_VERSION}")
set(MP7_VERSION
        "${MP7_VERSION}.${MP7_PATCH_VERSION}${MP7_EXTRA_VERSION}")
set(MP7_AUTHOR "Michael Pope (lead)")
set(MP7_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(MP7_DESCRIPTION "MP7 encoding and decoding exploration")
set(PROJECT_NAME "MP7 version ${MP7_VERSION}")
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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wold-style-cast \
    -Wnon-virtual-dtor -Wno-unused-parameter -Wno-invalid-offsetof")
endif()

mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

# set up RPATH
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_STANDARD 14)

include(GNUInstallDirs)

add_library(imageManipulation
        ${CMAKE_SOURCE_DIR}/cs225/lodepng/lodepng.cpp
        ${CMAKE_SOURCE_DIR}/cs225/HSLAPixel.cpp
        ${CMAKE_SOURCE_DIR}/cs225/PNG.cpp)
target_include_directories(imageManipulation
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/cs225/lodepng/>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/cs225/>)

add_library(disjointSets
        ${CMAKE_SOURCE_DIR}/source/dsets.cpp)
target_include_directories(disjointSets
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)

add_library(maze
        ${CMAKE_SOURCE_DIR}/source/maze.cpp)
target_include_directories(maze
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)
target_link_libraries(maze PUBLIC disjointSets imageManipulation)

add_library(mazeReader
        ${CMAKE_SOURCE_DIR}/source/mazereader.cpp)
target_include_directories(mazeReader
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)
target_link_libraries(mazeReader PUBLIC imageManipulation)

add_executable(main
        ${CMAKE_SOURCE_DIR}/source/main.cpp)
target_link_libraries(main PUBLIC mazeReader maze disjointSets imageManipulation)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Export MP7 as a CMake package
#install(FILES Lab_MP7Config.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MP7)
#install(EXPORT MP7
#        NAMESPACE MP7::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MP7)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/MP7.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/MP7.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_MP7)
endif()

