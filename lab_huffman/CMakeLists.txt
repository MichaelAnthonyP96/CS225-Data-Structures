cmake_minimum_required(VERSION 3.15)

# set project metadata ########################################################
set(HUFFMAN_MAJOR_VERSION 1)
set(HUFFMAN_MINOR_VERSION 0)
set(HUFFMAN_PATCH_VERSION 0)
set(HUFFMAN_EXTRA_VERSION "" CACHE STRING "HUFFMAN extra version string")
set(HUFFMAN_VERSION "${HUFFMAN_MAJOR_VERSION}.${HUFFMAN_MINOR_VERSION}")
set(HUFFMAN_VERSION
        "${HUFFMAN_VERSION}.${HUFFMAN_PATCH_VERSION}${HUFFMAN_EXTRA_VERSION}")
set(HUFFMAN_AUTHOR "Michael Pope (lead)")
set(HUFFMAN_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(HUFFMAN_DESCRIPTION "Huffman encoding and decoding exploration")
set(PROJECT_NAME "HUFFMAN version ${HUFFMAN_VERSION}")
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

add_library(binaryFileIO SHARED
        "${CMAKE_SOURCE_DIR}/source/binary_file_reader.cpp"
        "${CMAKE_SOURCE_DIR}/source/binary_file_writer.cpp")
target_include_directories(binaryFileIO
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Include>)

add_library(encoderDecoder
        ${CMAKE_SOURCE_DIR}/source/decoder.cpp
        ${CMAKE_SOURCE_DIR}/source/encoder.cpp)
target_include_directories(encoderDecoder
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Include>)
target_link_libraries(encoderDecoder PUBLIC binaryFileIO huffmanTree)

add_executable(decoder
        ${CMAKE_SOURCE_DIR}/source/decoder_prog.cpp)
target_include_directories(decoder
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Include>)
target_link_libraries(decoder PUBLIC encoderDecoder binaryFileIO)

add_executable(encoder
        ${CMAKE_SOURCE_DIR}/source/encoder_prog.cpp)
target_include_directories(encoder
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Include>)
target_link_libraries(encoder PUBLIC encoderDecoder binaryFileIO)

add_library(frequency
        ${CMAKE_SOURCE_DIR}/source/frequency.cpp)
target_include_directories(frequency
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Include>)

add_library(printTree
        ${CMAKE_SOURCE_DIR}/source/print_as_ascii.cpp)
target_include_directories(printTree
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Include>)
target_link_libraries(printTree PUBLIC binaryFileIO)

add_library(huffmanTree
        ${CMAKE_SOURCE_DIR}/source/huffman_tree.cpp)
target_include_directories(huffmanTree
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/source>)
target_link_libraries(huffmanTree PUBLIC frequency binaryFileIO printTree)

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