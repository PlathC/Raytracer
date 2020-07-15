
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
    constexpr double aspectRatio = 16. / 16.;

    constexpr uint16_t width           = 500;
    const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
    constexpr uint16_t channel         = 3;
    constexpr uint16_t samplesPerPixel = 10;
    const uint8_t maxDepth             = 50;

    glm::vec3 lookFrom = glm::vec3{0, 0, 4};
    glm::vec3 lookAt   = glm::vec3{0, 0, 0};
    glm::vec3 vup      = glm::vec3{0., 1., 0.};
    float distToFocus  = 10.f;
    float aperture     = 0.0f;

    rt::Environment environment;

    rt::ObjLoader loader{"./samples/suzanne.obj"};
    environment.Add(std::make_shared<rt::BVHNode>(*loader.Parse(), 0, 1));

    auto scene = rt::Scene{
            rt::Camera(lookFrom, lookAt, vup, 40, aspectRatio, aperture, distToFocus),
            {width, height, channel},
            samplesPerPixel,
            maxDepth,
            {0.7, 0.7, 0.7},
            environment
    };

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