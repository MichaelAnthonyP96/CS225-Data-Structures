cmake_minimum_required(VERSION 3.15)
project(lab_btree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cs225)
include_directories(cs225/catch)
include_directories(cs225/lodepng)

add_executable(lab_btree
        cs225/catch/catch.hpp
        cs225/catch/catchmain.cpp
        cs225/lodepng/lodepng.cpp
        cs225/lodepng/lodepng.h
        cs225/HSLAPixel.cpp
        cs225/HSLAPixel.h
        cs225/PNG.cpp
        cs225/PNG.h
        cs225/RGB_HSL.h
        tests/basic.cpp)

# set project metadata ########################################################
set(BTREES_MAJOR_VERSION 1)
set(BTREES_MINOR_VERSION 0)
set(BTREES_PATCH_VERSION 0)
set(BTREES_EXTRA_VERSION "" CACHE STRING "BTrees extra version string")
set(BTREES_VERSION "${BTREES_MAJOR_VERSION}.${BTREES_MINOR_VERSION}")
set(BTREES_VERSION
        "${BTREES_VERSION}.${BTREES_PATCH_VERSION}${BTREES_EXTRA_VERSION}")
set(BTREES_AUTHOR "Michael Pope (lead)")
set(BTREES_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(BTREES_DESCRIPTION "Learn about BTrees and how they can be used to implement the dictionary ADT.")
set(PROJECT_NAME "BTREES version ${BTREES_VERSION}")
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

include(GNUInstallDirs)

add_library(bTree
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/btree.h)
target_include_directories(bTree
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>)
set_target_properties(bTree PROPERTIES LINKER_LANGUAGE CXX)

add_executable(dictRacer
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/dict_racer.cpp)
target_include_directories(dictRacer
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)
target_link_libraries(dictRacer PUBLIC bTree)
set_target_properties(dictRacer PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Export BTREES as a CMake package
#install(FILES Lab_BTREESConfig.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BTREES)
#install(EXPORT BTREES
#        NAMESPACE BTREES::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BTREES)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/BTREES.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/BTREES.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_BTREES)
endif()
