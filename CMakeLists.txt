cmake_minimum_required(VERSION 3.7)
project(PlaneFinder)

set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES main.cpp)
#add_executable(PlaneFinder ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "-I/usr/local/Cellar/eigen/3.3.3/include/eigen3")


# my plane finder program
add_executable(planeFinder
        planeFinder.cpp
        SimplePly.h
        SimplePly.cpp
        rply.h
        rply.c
        Plane.cpp Plane.h)


# playground
add_executable(playground playground.cpp SimplePly.h
        SimplePly.cpp
        rply.h
        rply.c)