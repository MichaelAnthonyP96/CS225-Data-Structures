cmake_minimum_required(VERSION 3.15)
project(lab_ml)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cs225)
include_directories(cs225/catch)
include_directories(cs225/lodepng)

add_executable(lab_ml
        cs225/catch/catch.hpp
        cs225/catch/catchmain.cpp
        cs225/lodepng/lodepng.cpp
        cs225/lodepng/lodepng.h
        cs225/HSLAPixel.cpp
        cs225/HSLAPixel.h
        cs225/PNG.cpp
        cs225/PNG.h
        cs225/RGB_HSL.h
        tests/unit_tests.cpp
        edge.h
        graph.cpp
        graph.h
        lab_graphs_random.cpp
        lab_graphs_random.h
        main.cpp
        NimLearner.cpp
        NimLearner.h)
