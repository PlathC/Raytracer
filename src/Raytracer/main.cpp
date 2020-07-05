
#include <chrono>
#include <iostream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "Raytracer/Object/Triangle.hpp"
#include "Raytracer/Object/TriangleMesh.hpp"
#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/Metal.hpp"
#include "Raytracer/Utils/Loader/ObjLoader.hpp"
#include "Raytracer/Utils/Scene.hpp"

int main(int argc, char** argv)
{
    constexpr double aspectRatio = 16. / 9.;

    constexpr uint16_t width           = 300;
    const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
    constexpr uint16_t channel         = 3;
    constexpr uint16_t samplesPerPixel = 20;
    const uint8_t maxDepth             = 50;

    glm::vec3 lookFrom = glm::vec3{13, 2, 3};
    glm::vec3 lookAt   = glm::vec3{0., 0., 0.};
    glm::vec3 vup      = glm::vec3{0., 1., 0.};
    float distToFocus = 10.f;
    float aperture    = 0.1f;

    rt::SceneSettings settings = rt::SceneSettings {
        rt::Camera{lookFrom, lookAt, vup, 20, aspectRatio, aperture, distToFocus},
        rt::SceneSettings::ImageSettings{width, height, channel},
        samplesPerPixel, maxDepth};

    rt::Environment environment = rt::Environment::RandomEnvironment();

    //environment.Clear();
    //environment.Add(rt::TriangleMesh::CreateSphere(2, 10));

    //rt::ObjLoader loader{"./samples/uvsphere.obj"};
    //environment.Add(loader.Parse());

    rt::Scene scene = rt::Scene { settings, std::move(environment) };

    auto timeStart = std::chrono::high_resolution_clock::now();
    auto img = scene.GenerateImage();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto passedTime = std::chrono::duration<double, std::milli>(timeEnd - timeStart).count();

    std::cout << "Scene rendered in : " << passedTime << "ms" << std::endl;

    stbi_write_png("output.png", width, height, channel, img.data(), width*channel);

    return EXIT_SUCCESS;
}