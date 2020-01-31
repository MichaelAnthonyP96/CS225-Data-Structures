cmake_minimum_required(VERSION 3.15)
project(lab_quacks)

# set project metadata ########################################################
set(QUACKS_MAJOR_VERSION 1)
set(QUACKS_MINOR_VERSION 0)
set(QUACKS_PATCH_VERSION 0)
set(QUACKS_EXTRA_VERSION "" CACHE STRING "QuackS extra version string")
set(QUACKS_VERSION "${QUACKS_MAJOR_VERSION}.${QUACKS_MINOR_VERSION}")
set(QUACKS_VERSION
        "${QUACKS_VERSION}.${QUACKS_PATCH_VERSION}${QUACKS_EXTRA_VERSION}")
set(QUACKS_AUTHOR "Michael Pope (lead)")
set(QUACKS_AUTHOR_EMAIL "michaelpope96@gmail.com")
set(QUACKS_DESCRIPTION "Stacks and Queues lab")
set(PROJECT_NAME "QUACKS version ${QUACKS_VERSION}")
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
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++" )

# set up RPATH
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_CXX_STANDARD 11)

include(GNUInstallDirs)

add_library(Quack
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/quackfun.h)
target_include_directories(Quack
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/>)
set_target_properties(Quack PROPERTIES LINKER_LANGUAGE CXX)

add_library(Stack
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/stack.cpp)
target_include_directories(Stack
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>)
set_target_properties(Stack PROPERTIES LINKER_LANGUAGE CXX)

add_library(Queue
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/queue.cpp)
target_include_directories(Queue
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>)
set_target_properties(Queue PROPERTIES LINKER_LANGUAGE CXX)
#[[add_custom_command(
        OUTPUT blueue.out
        COMMAND "${CMAKE_C_COMPILER}" ${CMAKE_CURRENT_SOURCE_DIR}/Include/blueue.cpp --precompile -o blueue
        MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/Include/blueue.cpp
        COMMENT "Preprocessing blueue"
        VERBATIM
)]]

add_library(Exercises
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/exercises.cpp)
target_include_directories(Exercises
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>)
set_target_properties(Exercises PROPERTIES LINKER_LANGUAGE CXX)

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp)
target_include_directories(main
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>)
target_link_libraries(main PUBLIC Queue Stack Quack Exercises)

if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Export QUACKS as a CMake package
#install(FILES Lab_QuacksConfig.cmake
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QUACKS)
#install(EXPORT QUACKS
#        NAMESPACE QUACKS::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QUACKS)

# Documentation
if(BUILD_DOCUMENTATION)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/QUACKS.cfg.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/QUACKS.cfg)
    set(documentation ${CMAKE_CURRENT_BINARY_DIR}/docs)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_command(OUTPUT ${documentation}
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            MAIN_DEPENDENCY ${doxyfile} ${doxyfile_in}
            DEPENDS ${doxyfile} ${doxy_extra_files}
            COMMENT "Generating documentation")
    add_custom_target(docs ALL DEPENDS ${documentation})
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/Lab_Quacks)
endif()