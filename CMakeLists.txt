cmake_minimum_required(VERSION 3.16)
project(Raytracer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(RT_HEADER
        include/Raytracer/Math/Core.hpp
        include/Raytracer/Math/Vec.hpp
        include/Raytracer/Math/Ray.hpp
        include/Raytracer/Math/Math.hpp
        include/Raytracer/Utils/Camera.hpp
        include/Raytracer/Object/Hittable.hpp
        include/Raytracer/Object/Sphere.hpp
        include/Raytracer/Object/Triangle.hpp
        include/Raytracer/Object/PolygonMesh.hpp
        include/Raytracer/Object/TriangleMesh.hpp
        include/Raytracer/Object/Environment.hpp
        include/Raytracer/Material/Material.hpp
        include/Raytracer/Material/Lambertian.hpp
        include/Raytracer/Material/Metal.hpp
        include/Raytracer/Material/Dielectric.hpp
        include/Raytracer/Utils/Scene.hpp)

set(RT_SRC
        src/Raytracer/main.cpp
        src/Raytracer/Utils/Camera.cpp
        src/Raytracer/Object/Sphere.cpp
        src/Raytracer/Object/Environment.cpp
        src/Raytracer/Material/Lambertian.cpp
        src/Raytracer/Material/Metal.cpp
        src/Raytracer/Material/Dielectric.cpp
        src/Raytracer/Utils/Scene.cpp
        src/Raytracer/Object/Triangle.cpp
        src/Raytracer/Object/PolygonMesh.cpp
        src/Raytracer/Object/TriangleMesh.cpp)

add_executable(Raytracer ${RT_HEADER} ${RT_SRC} )

target_include_directories(Raytracer SYSTEM PRIVATE include)
target_include_directories(Raytracer SYSTEM PRIVATE external)
