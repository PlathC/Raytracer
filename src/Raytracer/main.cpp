
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

    constexpr uint16_t width           = 300;
    const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
    constexpr uint16_t channel         = 3;
    constexpr uint16_t samplesPerPixel = 20;
    const uint8_t maxDepth             = 50;

    glm::vec3 lookFrom = glm::vec3{1,  1,  4};
    glm::vec3 lookAt   = glm::vec3{0, 0, 0};
    glm::vec3 vup      = glm::vec3{0., 1., 0.};
    float distToFocus  = 10.f;
    float aperture     = 0.0f;

    rt::SceneSettings settings = rt::SceneSettings {
        rt::Camera{lookFrom, lookAt, vup, 40, aspectRatio, aperture, distToFocus},
        rt::SceneSettings::ImageSettings{width, height, channel},
        samplesPerPixel, maxDepth, glm::vec3(0.7, 0.7, 0.7)};

    rt::Environment environment;
    auto groundMaterial = std::make_shared<rt::Lambertian>(std::make_shared<rt::SolidColor>(glm::vec3(0.2, 0.2, 0.2)));
    environment.Add(std::make_shared<rt::Plane<1>>(glm::vec2(-50, -50), glm::vec2(50, 50), -1, groundMaterial));

    auto light = std::make_shared<rt::DiffuseLight>(std::make_shared<rt::SolidColor>(glm::vec3(20., 20., 20)));
    environment.Add(std::make_shared<rt::Plane<0>>(glm::vec2(1, 1), glm::vec2(5, 5), -3, light));

    rt::ObjLoader objLoader{"samples/suzanne.obj"};

    auto sphere = std::make_shared<rt::Sphere>(glm::vec3(0, 0, 0), 1, nullptr);
    auto cyan = std::make_shared<rt::SolidColor>(glm::vec3(0., 1., 1.));
    //environment.Add(std::make_shared<rt::ConstantDensityMedium>(sphere, cyan, 0.1));

    environment.Add(std::make_shared<rt::BVHNode>(*objLoader.Parse(), 0, 1));


    rt::Renderer scene = rt::Renderer {settings, environment };

    auto timeStart = std::chrono::high_resolution_clock::now();
    auto img = scene.GenerateImage();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto passedTime = std::chrono::duration<double, std::milli>(timeEnd - timeStart).count();

    std::cout << "Renderer rendered in : " << passedTime << "ms" << std::endl;

    stbi_write_png("output.png", width, height, channel, img.data(), width*channel);

    return EXIT_SUCCESS;
}