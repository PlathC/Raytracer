#include <iostream>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "Raytracer/Object/Triangle.hpp"
#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/Metal.hpp"
#include "Raytracer/Utils/Scene.hpp"

int main(int argc, char** argv)
{
    constexpr double aspectRatio = 16.0 / 9.0;

    constexpr uint16_t width           = 720;
    const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
    constexpr uint16_t channel         = 3;
    constexpr uint16_t samplesPerPixel = 50;
    const uint8_t maxDepth             = 50;

    rt::Point3 lookFrom = rt::Point3{0., 0., 3.};
    rt::Point3 lookAt   = rt::Point3{0., 0.2, 0};
    rt::Vec3 vup        = rt::Vec3{0, 1, 0};
    double distToFocus  = 9.0;
    double aperture     = 0.01;

    rt::SceneSettings settings = rt::SceneSettings {
        rt::Camera{lookFrom, lookAt, vup, 30, aspectRatio, aperture, distToFocus},
        rt::SceneSettings::ImageSettings{width, height, channel},
        samplesPerPixel, maxDepth};

    rt::Environment environment;
    environment.Add(std::make_unique<rt::Triangle>(
            rt::Vec3(-1., 0., 0.),
            rt::Vec3(1., 1., 0.),
            rt::Vec3(0., 1., 0.),

            std::make_unique<rt::Metal>(rt::Color{0., 1., 1.}, 0.9)
    ));
    environment.Add(std::make_unique<rt::Triangle>(
            rt::Vec3(-1., 0., 0.),
            rt::Vec3(0., 1., -1.),
            rt::Vec3(0., 0., 0.),

            std::make_unique<rt::Lambertian>(rt::Color{1., 0., 1.})
    ));

    rt::Scene scene = rt::Scene { settings, std::move(environment) };
    auto img = scene.GenerateImage();

    stbi_write_png("output.png", width, height, channel, img.data(), width*channel);

    return EXIT_SUCCESS;
}