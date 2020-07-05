
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
    constexpr double aspectRatio = 1. / 1.;

    constexpr uint16_t width           = 300;
    const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
    constexpr uint16_t channel         = 3;
    constexpr uint16_t samplesPerPixel = 50;
    const uint8_t maxDepth             = 50;

    glm::vec3 lookFrom = glm::vec3{0., 5.0, -2.};
    glm::vec3 lookAt   = glm::vec3{0., 0., 0.};
    glm::vec3 vup      = glm::vec3{0, 0., 1.};
    float distToFocus = 9.0f;
    float aperture    = 0.1f;

    rt::SceneSettings settings = rt::SceneSettings {
        rt::Camera{lookFrom, lookAt, vup, 50, aspectRatio, aperture, distToFocus},
        rt::SceneSettings::ImageSettings{width, height, channel},
        samplesPerPixel, maxDepth};

    rt::Environment environment;

    uint32_t numFaces = 1;
    std::vector<uint32_t> faceIndex   = {4};
    std::vector<uint32_t> vertexIndex = {0, 1, 2, 3};
    std::vector<glm::vec3> P = {
            glm::vec3(-5, -5,  5), glm::vec3( 5, -5,  5),
            glm::vec3( 5, -5, -5), glm::vec3(-5, -5, -5)
    };

    //environment.Add(std::make_unique<rt::TriangleMesh>(numFaces,
    //        faceIndex, vertexIndex, P, std::vector<rt::Vec3>{},
    //        std::make_unique<rt::Lambertian>(rt::Color{0.5, 0.5, 1.}))
    //        );

    //environment.Add(std::make_unique<rt::Triangle>(
    //        glm::vec3( 5, -5,  5),
    //        glm::vec3(-5, -5,  5),
    //        glm::vec3( 5, -5, -5),
    //        std::make_unique<rt::Lambertian>(glm::vec3{1, 0., 0.}))
    //     );
//
    //environment.Add(std::make_unique<rt::Triangle>(
    //        glm::vec3( -5,  -5,  -5),
    //        glm::vec3( -5, -5,  5),
    //        glm::vec3(  5,  -5,  -5),
    //        std::make_unique<rt::Lambertian>(glm::vec3{0.0, 0.0, 1.}))
    //);

    //environment.Clear();
    environment.Add(rt::TriangleMesh::CreateSphere(2, 10));

    //auto mesh = std::make_unique<rt::TriangleMesh>();
    rt::ObjLoader loader{"./samples/cube.obj"};
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