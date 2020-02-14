cmake_minimum_required(VERSION 3.15)
project(mp6)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cs225)
include_directories(cs225/catch)
include_directories(cs225/lodepng)

add_executable(mp6
        cs225/catch/catch.hpp
        cs225/catch/catchmain.cpp
        cs225/lodepng/lodepng.cpp
        cs225/lodepng/lodepng.h
        cs225/HSLAPixel.cpp
        cs225/HSLAPixel.h
        cs225/PNG.cpp
        cs225/PNG.h
        cs225/RGB_HSL.h
        gdb-examples/list.cpp
        gdb-examples/loop.cpp
        gdb-examples/playground.cpp
        gdb-examples/recurse.cpp
        gdb-examples/swap.cpp
        gdb-examples/switch.cpp
        tests/unit_tests.cpp
        main.cpp
        skipList.cpp
        skipList.h
        skipList_given.cpp
        skipNode.cpp
        skipNode.h)

cmake_minimum_required(VERSION 3.15)

# set project metadata ########################################################
set(MP6_MAJOR_VERSION 1)
set(MP6_MINOR_VERSION 0)
set(MP6_PATCH_VERSION 0)
set(MP6_EXTRA_VERSION "" CACHE STRING "MP6 extra version string")
set(MP6_VERSION "${MP6_MAJOR_VERSION}.${MP6_MINOR_VERSION}")
set(MP6_VERSION
        "${MP6_VERSION}.${MP6_PATCH_VERSION}${MP6_EXTRA_VERSION}")
set(MP6_AUTHOR "Michael Pope (lead)")
set(MP6_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(MP6_DESCRIPTION "MP6 skip lists implementation")
set(PROJECT_NAME "MP6 version ${MP6_VERSION}")
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

# Export MP6 as a CMake package
#install(FILES Lab_MP6Config.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MP6)
#install(EXPORT MP6
#        NAMESPACE MP6::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MP6)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/MP6.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/MP6.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_MP6)
endif()

