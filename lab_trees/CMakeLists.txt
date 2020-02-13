cmake_minimum_required(VERSION 3.15)
project(lab_trees)

# set project metadata ########################################################
set(TREES_MAJOR_VERSION 1)
set(TREES_MINOR_VERSION 0)
set(TREES_PATCH_VERSION 0)
set(TREES_EXTRA_VERSION "" CACHE STRING "Trees extra version string")
set(TREES_VERSION "${TREES_MAJOR_VERSION}.${TREES_MINOR_VERSION}")
set(TREES_VERSION
        "${TREES_VERSION}.${TREES_PATCH_VERSION}${TREES_EXTRA_VERSION}")
set(TREES_AUTHOR "Michael Pope (lead)")
set(TREES_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(TREES_DESCRIPTION "Binary Tree implementation and manipulation")
set(PROJECT_NAME "TREES version ${TREES_VERSION}")
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

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

add_library(binaryTree
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/binarytree.h)
target_include_directories(binaryTree
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>)
set_target_properties(binaryTree PROPERTIES LINKER_LANGUAGE CXX)


add_library(treeTraversal
        ${CMAKE_CURRENT_SOURCE_DIR}/TreeTraversals/InorderTraversal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TreeTraversals/PreorderTraversal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/TreeTraversals/TreeTraversal.h)
target_include_directories(treeTraversal
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/TreeTraversals/>)
set_target_properties(treeTraversal PROPERTIES LINKER_LANGUAGE CXX)

add_library(coloredOut
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/coloredout.cpp)
target_include_directories(coloredOut
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>)


if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Export TREES as a CMake package
#install(FILES Lab_TREESConfig.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TREES)
#install(EXPORT TREES
#        NAMESPACE TREES::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TREES)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/TREES.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/TREES.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_TREES)
endif()

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp)
target_link_libraries(main PUBLIC treeTraversal binaryTree coloredOut)

