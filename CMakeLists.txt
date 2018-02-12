cmake_minimum_required(VERSION 3.5)
project(Fractals)

set(CMAKE_CXX_STANDARD 11)


add_executable(julia
        MiscMap/mandelbrot.cpp
        MiscMap/func.h
        MiscMap/func.cpp
        MiscMap/Iterate.h
        )

add_executable(mandelbrot
        MiscMap/mandelbrot.cpp
        MiscMap/func.h
        MiscMap/func.cpp
        MiscMap/Iterate.h
        )