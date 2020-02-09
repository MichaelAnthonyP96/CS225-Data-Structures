cmake_minimum_required(VERSION 3.15)
project(lab_debug)

set(CMAKE_CXX_STANDARD 14)

# set project metadata ########################################################
set(DEBUG_MAJOR_VERSION 1)
set(DEBUG_MINOR_VERSION 0)
set(DEBUG_PATCH_VERSION 0)
set(DEBUG_EXTRA_VERSION "" CACHE STRING "DEBUG extra version string")
set(DEBUG_VERSION "${DEBUG_MAJOR_VERSION}.${DEBUG_MINOR_VERSION}")
set(DEBUG_VERSION
        "${DEBUG_VERSION}.${DEBUG_PATCH_VERSION}${DEBUG_EXTRA_VERSION}")
set(DEBUG_AUTHOR "Michael Pope (lead)")
set(DEBUG_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(DEBUG_DESCRIPTION "Binary Tree implementation and manipulation")
set(PROJECT_NAME "DEBUG version ${DEBUG_VERSION}")
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

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

add_library(imageManipulation
        ${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodepng/lodepng.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cs225/HSLAPixel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/cs225/PNG.cpp)
target_include_directories(imageManipulation
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cs225/lodePNG>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cs225/>)
set_target_properties(imageManipulation PROPERTIES LINKER_LANGUAGE CXX)

add_library(sketchify
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/sketchify.cpp)
target_include_directories(sketchify
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>)
target_link_libraries(sketchify PUBLIC imageManipulation)
set_target_properties(sketchify PROPERTIES LINKER_LANGUAGE CXX)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp)
target_link_libraries(main PUBLIC imageManipulation sketchify)

# Export DEBUG as a CMake package
#install(FILES Lab_DEBUGConfig.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DEBUG)
#install(EXPORT DEBUG
#        NAMESPACE DEBUG::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DEBUG)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/DEBUG.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/DEBUG.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_DEBUG)
endif()
