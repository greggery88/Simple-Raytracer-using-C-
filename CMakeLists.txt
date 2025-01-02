cmake_minimum_required(VERSION 3.30)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracing main.cpp
        vec3.h
        color.h
        ray.h
        hittable.h
        sphere.h
        hittable_list.h
        rtpproject.h
        interval.h
        camera.h
        material.h
        presets.h
        cmake-build-release/AAbb.h)
