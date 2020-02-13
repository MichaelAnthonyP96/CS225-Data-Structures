cmake_minimum_required(VERSION 3.15)

# set project metadata ########################################################
set(INHERITANCE_MAJOR_VERSION 1)
set(INHERITANCE_MINOR_VERSION 0)
set(INHERITANCE_PATCH_VERSION 0)
set(INHERITANCE_EXTRA_VERSION "" CACHE STRING "INHERITANCE extra version string")
set(INHERITANCE_VERSION "${INHERITANCE_MAJOR_VERSION}.${INHERITANCE_MINOR_VERSION}")
set(INHERITANCE_VERSION
        "${INHERITANCE_VERSION}.${INHERITANCE_PATCH_VERSION}${INHERITANCE_EXTRA_VERSION}")
set(INHERITANCE_AUTHOR "Michael Pope (lead)")
set(INHERITANCE_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(INHERITANCE_DESCRIPTION "INHERITANCE encoding and decoding exploration")
set(PROJECT_NAME "INHERITANCE version ${INHERITANCE_VERSION}")
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

add_library(shapes
        ${CMAKE_SOURCE_DIR}/source/circle.cpp
        ${CMAKE_SOURCE_DIR}/source/rectangle.cpp
        ${CMAKE_SOURCE_DIR}/source/shape.cpp
        ${CMAKE_SOURCE_DIR}/source/triangle.cpp
        ${CMAKE_SOURCE_DIR}/source/line.cpp
        ${CMAKE_SOURCE_DIR}/source/vector2.cpp)
target_include_directories(shapes
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)
target_link_libraries(shapes PUBLIC imageManipulation)

add_library(drawable
        ${CMAKE_SOURCE_DIR}/source/flower.cpp
        ${CMAKE_SOURCE_DIR}/source/truck.cpp)
target_include_directories(drawable
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)
target_link_libraries(drawable PUBLIC shapes imageManipulation)

add_executable(main
        ${CMAKE_SOURCE_DIR}/source/main.cpp)
target_link_libraries(main PUBLIC drawable shapes imageManipulation)



if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Export HUFFMAN as a CMake package
#install(FILES Lab_HUFFMANConfig.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HUFFMAN)
#install(EXPORT HUFFMAN
#        NAMESPACE HUFFMAN::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/HUFFMAN)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/HUFFMAN.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/HUFFMAN.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_HUFFMAN)
endif()
