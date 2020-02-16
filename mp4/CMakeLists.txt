cmake_minimum_required(VERSION 3.15)

# set project metadata ########################################################
set(MP4_MAJOR_VERSION 1)
set(MP4_MINOR_VERSION 0)
set(MP4_PATCH_VERSION 0)
set(MP4_EXTRA_VERSION "" CACHE STRING "MP4 extra version string")
set(MP4_VERSION "${MP4_MAJOR_VERSION}.${MP4_MINOR_VERSION}")
set(MP4_VERSION
        "${MP4_VERSION}.${MP4_PATCH_VERSION}${MP4_EXTRA_VERSION}")
set(MP4_AUTHOR "Michael Pope (lead)")
set(MP4_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(MP4_DESCRIPTION "MP4 encoding and decoding exploration")
set(PROJECT_NAME "MP4 version ${MP4_VERSION}")
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

add_library(traversals
        ${CMAKE_SOURCE_DIR}/imageTraversal/BFS.cpp
        ${CMAKE_SOURCE_DIR}/imageTraversal/DFS.cpp
        ${CMAKE_SOURCE_DIR}/imageTraversal/ImageTraversal.cpp)
target_include_directories(traversals
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/imageTraversal/>)
target_link_libraries(traversals PUBLIC imageManipulation Point)

add_library(animation
        ${CMAKE_SOURCE_DIR}/source/Animation.cpp
        ${CMAKE_SOURCE_DIR}/source/FloodFilledImage.cpp)
target_include_directories(animation
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)
target_link_libraries(animation PUBLIC imageManipulation Point traversals colorPicker)

add_library(Point
        ${CMAKE_SOURCE_DIR}/source/Point.cpp)
target_include_directories(Point
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>)

add_library(colorPicker
        ${CMAKE_SOURCE_DIR}/colorPicker/GradientColorPicker.cpp
        ${CMAKE_SOURCE_DIR}/colorPicker/GridColorPicker.cpp
        ${CMAKE_SOURCE_DIR}/colorPicker/MyColorPicker.cpp
        ${CMAKE_SOURCE_DIR}/colorPicker/RainbowColorPicker.cpp
        ${CMAKE_SOURCE_DIR}/colorPicker/SolidColorPicker.cpp)
target_include_directories(colorPicker
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/colorPicker/>)
target_link_libraries(colorPicker PUBLIC Point imageManipulation)

add_executable(main
        ${CMAKE_SOURCE_DIR}/source/main.cpp)
target_link_libraries(main PUBLIC traversals Point imageManipulation Point traversals colorPicker animation)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Export MP4 as a CMake package
#install(FILES Lab_MP4Config.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MP4)
#install(EXPORT MP4
#        NAMESPACE MP4::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MP4)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/MP4.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/MP4.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_MP4)
endif()

