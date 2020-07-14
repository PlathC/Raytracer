
#include <chrono>
#include <iostream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "Raytracer/Object/Plane.hpp"
#include "Raytracer/Object/ConstantDensityMedium.hpp"
#include "Raytracer/Object/Triangle.hpp"
#include "Raytracer/Object/TriangleMesh.hpp"
#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/DiffuseLight.hpp"
#include "Raytracer/Material/SolidColor.hpp"
#include "Raytracer/Material/Metal.hpp"
#include "Raytracer/Utils/Loader/ObjLoader.hpp"
#include "Raytracer/Utils/Renderer.hpp"

int main(int argc, char** argv)
{
    auto scene = rt::Scene::TwoSpheres();

    rt::Renderer renderer = rt::Renderer { scene };

    auto timeStart = std::chrono::high_resolution_clock::now();
    auto img = renderer.GenerateImage();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto passedTime = std::chrono::duration<double, std::milli>(timeEnd - timeStart).count();

    std::cout << "Renderer rendered in : " << passedTime << "ms" << std::endl;

    stbi_write_png("output.png", scene.imageSettings.width, scene.imageSettings.height, scene.imageSettings.channels,
            img.data(),  scene.imageSettings.width * scene.imageSettings.channels);

    return EXIT_SUCCESS;
}