cmake_minimum_required(VERSION 3.16)
project(Raytracer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

find_package(OpenImageDenoise)

if(OpenImageDenoise_FOUND)
    message("Found OpenImageDenoise library, enable denoise feature.")
    set(RAYTRACER_BUILD_DEFINITIONS
            ${RAYTRACER_BUILD_DEFINITIONS}
            RAYTRACER_WITH_OID)
endif()

# Based on https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
if (CMAKE_COMPILER_IS_GNUCC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(RAYTRACER_COMPILATION_FLAGS
                -Wall
                -Wextra
                -Wshadow
                -pedantic
                -Wnon-virtual-dtor
                -Wold-style-cast
                -Wcast-align
                -Wunused
                -Woverloaded-virtual
                -Wpedantic
                -Wconversion
                -Wsign-conversion
                -Wmisleading-indentation
                -Wduplicated-cond
                -Wduplicated-branches
                -Wlogical-op
                -Wnull-dereference
                -Wuseless-cast
                -Wdouble-promotion
                -Wformat=2)
    else()
        set(RAYTRACER_COMPILATION_FLAGS
                -DNDEBUG
                -Wall
                -Wextra
                -Wshadow
                -pedantic
                -Wnon-virtual-dtor
                -Wold-style-cast
                -Wcast-align
                -Wunused
                -Woverloaded-virtual
                -Wpedantic
                -Wconversion
                -Wsign-conversion
                -Wmisleading-indentation
                -Wduplicated-cond
                -Wduplicated-branches
                -Wlogical-op
                -Wnull-dereference
                -Wuseless-cast
                -Wdouble-promotion
                -Wformat=2)
    endif()
elseif (MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(RAYTRACER_COMPILATION_FLAGS
                /permissive-
                /EHs
                /W4
                /w14242
                /w14254
                /w14263
                /w14265
                /w14287
                /we4289
                /w14296
                /w14311
                /w14545
                /w14546
                /w14547
                /w14549
                /w14555
                /w14619
                /w14640
                /w14826
                /w14928
                /wd4201
                )
    else()
        set(RAYTRACER_COMPILATION_FLAGS
                /permissive-
                /EHs
                /W4
                /w14242
                /w14254
                /w14263
                /w14265
                /w14287
                /we4289
                /w14296
                /w14311
                /w14545
                /w14546
                /w14547
                /w14549
                /w14555
                /w14619
                /w14640
                /w14826
                /w14928
                /wd4201)
    endif()
endif ()

set(RT_HEADER
        include/Raytracer/Math/Math.hpp
        include/Raytracer/Math/Vec.hpp
        include/Raytracer/Math/Ray.hpp
        include/Raytracer/Math/Aabb.hpp
        include/Raytracer/Math/Perlin.hpp
        include/Raytracer/Utils/Camera.hpp
        include/Raytracer/Object/IHittable.hpp
        include/Raytracer/Object/Sphere.hpp
        include/Raytracer/Object/Triangle.hpp
        include/Raytracer/Object/TriangleMesh.hpp
        include/Raytracer/Object/Environment.hpp
        include/Raytracer/Object/ICollection.hpp
        include/Raytracer/Material/Material.hpp
        include/Raytracer/Material/Lambertian.hpp
        include/Raytracer/Material/Metal.hpp
        include/Raytracer/Material/Dielectric.hpp
        include/Raytracer/Utils/Renderer.hpp
        include/Raytracer/Utils/MeshLoader.hpp
        include/Raytracer/Utils/Loader/ObjLoader.hpp
        include/Raytracer/Object/Vertex.hpp
        include/Raytracer/Object/MovingSphere.hpp
        include/Raytracer/Object/BvhNode.hpp
        include/Raytracer/Material/Texture.hpp
        include/Raytracer/Material/SolidColor.hpp
        include/Raytracer/Material/CheckerTexture.hpp
        include/Raytracer/Material/PerlinTexture.hpp
        include/Raytracer/Material/ImageTexture.hpp
        include/Raytracer/Material/DiffuseLight.hpp
        include/Raytracer/Object/Plane.hpp
        include/Raytracer/Object/Plane.inl
        include/Raytracer/Object/FlipFace.hpp
        include/Raytracer/Object/Box.hpp
        include/Raytracer/Object/Translation.hpp
        include/Raytracer/Object/Rotation.hpp
        include/Raytracer/Object/Rotation.inl
        include/Raytracer/Object/ConstantDensityMedium.hpp
        include/Raytracer/Material/Isotropic.hpp
        include/Raytracer/Core/ThreadPool.hpp
        include/Raytracer/Utils/Scene.hpp
        include/Raytracer/Math/OrthonormalBase.hpp
        include/Raytracer/Math/ProbabilityDensityFunction.hpp
        )

set(RT_SRC
        src/Raytracer/main.cpp
        src/Raytracer/Utils/Camera.cpp
        src/Raytracer/Object/Sphere.cpp
        src/Raytracer/Object/Environment.cpp
        src/Raytracer/Material/Lambertian.cpp
        src/Raytracer/Material/Metal.cpp
        src/Raytracer/Material/Dielectric.cpp
        src/Raytracer/Utils/Renderer.cpp
        src/Raytracer/Object/Triangle.cpp
        src/Raytracer/Object/TriangleMesh.cpp
        src/Raytracer/Utils/Loader/ObjLoader.cpp
        src/Raytracer/Object/MovingSphere.cpp
        src/Raytracer/Math/Aabb.cpp
        src/Raytracer/Object/BvhNode.cpp
        src/Raytracer/Material/SolidColor.cpp
        src/Raytracer/Material/CheckerTexture.cpp
        src/Raytracer/Math/Perlin.cpp
        src/Raytracer/Material/PerlinTexture.cpp
        src/Raytracer/Material/ImageTexture.cpp
        src/Raytracer/Material/DiffuseLight.cpp
        src/Raytracer/Material/Material.cpp
        src/Raytracer/Object/FlipFace.cpp
        src/Raytracer/Object/Box.cpp
        src/Raytracer/Object/Translation.cpp
        src/Raytracer/Object/ConstantDensityMedium.cpp
        src/Raytracer/Material/Isotropic.cpp
        src/Raytracer/Core/ThreadPool.cpp
        src/Raytracer/Utils/Scene.cpp
        src/Raytracer/Math/OrthonormalBase.cpp
        src/Raytracer/Math/ProbabilityDensityFunction.cpp
        src/Raytracer/Object/Plane.cpp)

add_executable(Raytracer ${RT_HEADER} ${RT_SRC} )

target_compile_options(${PROJECT_NAME} PRIVATE ${RAYTRACER_COMPILATION_FLAGS})

if (CMAKE_COMPILER_IS_GNUCC)
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
endif()

target_include_directories(Raytracer SYSTEM PRIVATE include)
target_include_directories(Raytracer SYSTEM PRIVATE external)

target_include_directories(Raytracer SYSTEM PRIVATE OpenImageDenoise::OpenImageDenoise)

target_compile_definitions(Raytracer PUBLIC ${RAYTRACER_BUILD_DEFINITIONS})

target_link_libraries(Raytracer PRIVATE OpenImageDenoise)

add_custom_target(copy-runtime-files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/samples ${CMAKE_BINARY_DIR}/samples
        DEPENDS ${MY_TARGET})
