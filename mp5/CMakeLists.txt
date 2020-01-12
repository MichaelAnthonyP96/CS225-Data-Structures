cmake_minimum_required(VERSION 3.15)
project(mp5)

# set project metadata ########################################################
set(MP5_MAJOR_VERSION 1)
set(MP5_MINOR_VERSION 0)
set(MP5_PATCH_VERSION 0)
set(MP5_EXTRA_VERSION "" CACHE STRING "MP5 extra version string")
set(MP5_VERSION "${MP5_MAJOR_VERSION}.${MP5_MINOR_VERSION}")
set(MP5_VERSION
        "${MP5_VERSION}.${MP5_PATCH_VERSION}${MP5_EXTRA_VERSION}")
set(MP5_AUTHOR "Michael Pope (lead)")
set(MP5_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(MP5_DESCRIPTION "KD Tree implementation and use for a photo mosaic")
set(PROJECT_NAME "MP5 version ${MP5_VERSION}")
project(${PROJECT_NAME} CXX C)

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

#include_directories(.)
#include_directories(cs225)
#include_directories(cs225/catch)
#include_directories(cs225/lodepng)
#include_directories(util)

include(GNUInstallDirs)

add_library(imageManipulation
        ${CMAKE_CURRENT_SOURCE_DIR}/cs225/HSLAPixel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng/lodepng.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cs225/PNG.cpp)
target_include_directories(imageManipulation
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cs225/>)

add_library(util
        ${CMAKE_CURRENT_SOURCE_DIR}/util/coloredout.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/util/util.cpp)
target_include_directories(util
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/util>)

add_library(mp5
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/kdtree.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/maptiles.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/mosaiccanvas.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/point.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/sourceimage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/tileimage.cpp)
target_link_libraries(mp5 PUBLIC util imageManipulation)
target_include_directories(mp5
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(main PUBLIC mp5 util imageManipulation)
target_include_directories(main
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/
        ${CMAKE_CURRENT_SOURCE_DIR}/cs225/
        ${CMAKE_CURRENT_SOURCE_DIR}/util/
        )

# Export MP5 as a CMake package
#install(FILES MP5Config.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MP5)
#install(EXPORT MP5
#        NAMESPACE MP5::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MP5)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/MP2.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/MP2.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/MP2)
endif()
