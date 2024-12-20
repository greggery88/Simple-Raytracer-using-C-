cmake_minimum_required(VERSION 3.30)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracing main.cpp
        vec3.h
        color.h
        ray.h)
