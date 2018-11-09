cmake_minimum_required(VERSION 3.5)
project(Fractals)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall")

set(CMAKE_CXX_FLAGS "-O3 -g -Wall")

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(julia
        MiscMap/julia.cpp
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
