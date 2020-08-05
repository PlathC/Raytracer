//
// Created by Platholl on 14/07/2020.
//


#include "Raytracer/Material/DiffuseLight.hpp"
#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/SolidColor.hpp"
#include "Raytracer/Object/BvhNode.hpp"
#include "Raytracer/Object/Sphere.hpp"
#include "Raytracer/Utils/Loader/ObjLoader.hpp"
#include "Raytracer/Utils/Scene.hpp"

namespace rt
{
    Scene Scene::RandomEnvironment()
    {
        constexpr float aspectRatio = 16.f / 9.f;

        constexpr uint16_t width           = 720;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 8;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{13,  2,  3};
        glm::vec3 lookAt   = glm::vec3{0, 0, 0};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        return Scene{
            Camera(lookFrom, lookAt, vup, 20, aspectRatio, aperture, distToFocus),
            { width, height, channel },
            samplesPerPixel,
            maxDepth,
            {1, 1, 1},
            Environment::RandomEnvironment()
        };
    }

    Scene Scene::TwoSpheres()
    {
        constexpr float aspectRatio = 16.f / 9.f;

        constexpr uint16_t width           = 720;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 8;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{13,  2,  3};
        glm::vec3 lookAt   = glm::vec3{0, 0, 0};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        return Scene{
                Camera(lookFrom, lookAt, vup, 20, aspectRatio, aperture, distToFocus),
                {width, height, channel},
                samplesPerPixel,
                maxDepth,
                {1, 1, 1},
                Environment::TwoSpheres()
        };
    }

    Scene Scene::TwoPerlinSpheres()
    {
        constexpr float aspectRatio = 16.f / 9.f;

        constexpr uint16_t width           = 720;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 8;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{13,  2,  3};
        glm::vec3 lookAt   = glm::vec3{0, 0, 0};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        return Scene{
                Camera(lookFrom, lookAt, vup, 20, aspectRatio, aperture, distToFocus),
                {width, height, channel},
                samplesPerPixel,
                maxDepth,
                {1, 1, 1},
                Environment::TwoPerlinSpheres()
        };
    }

    Scene Scene::Earth()
    {
        constexpr float aspectRatio = 16.f / 16.f;

        constexpr uint16_t width           = 720;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 8;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{13,  2,  3};
        glm::vec3 lookAt   = glm::vec3{0, 0, 0};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        return Scene{
                Camera(lookFrom, lookAt, vup, 20, aspectRatio, aperture, distToFocus),
                {width, height, channel},
                samplesPerPixel,
                maxDepth,
                {1, 1, 1},
                Environment::Earth()
        };
    }

    Scene Scene::SimpleLight()
    {
        constexpr float aspectRatio = 16.f / 9.f;

        constexpr uint16_t width           = 720;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 16;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{-15,  3,  20};
        glm::vec3 lookAt   = glm::vec3{0, 2, 0};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        return Scene{
                Camera(lookFrom, lookAt, vup, 20, aspectRatio, aperture, distToFocus),
                {width, height, channel},
                samplesPerPixel,
                maxDepth,
                {0, 0, 0},
                Environment::SimpleLight()
        };
    }

    Scene Scene::CornellBox()
    {
        constexpr float aspectRatio = 16.f / 16.f;

        constexpr uint16_t width           = 400;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 64;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{278, 278, -800};
        glm::vec3 lookAt   = glm::vec3{278, 278, 0};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        return Scene{
                Camera(lookFrom, lookAt, vup, 40, aspectRatio, aperture, distToFocus),
                {width, height, channel},
                samplesPerPixel,
                maxDepth,
                {0, 0, 0},
                Environment::CornellBox()
        };
    }

    Scene Scene::FinalScene()
    {
        constexpr float aspectRatio = 16.f / 16.f;

        constexpr uint16_t width           = 720;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 32;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{478, 278, -600};
        glm::vec3 lookAt   = glm::vec3{278, 278, 0};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        return Scene{
                Camera(lookFrom, lookAt, vup, 40, aspectRatio, aperture, distToFocus),
                {width, height, channel},
                samplesPerPixel,
                maxDepth,
                {0, 0, 0},
                Environment::FinalScene()
        };
    }

    Scene Scene::Suzanne()
    {
        constexpr float aspectRatio = 16.f / 16.f;

        constexpr uint16_t width           = 500;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 8;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{0, 0, 5};
        glm::vec3 lookAt   = glm::vec3{0, 0, 0};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        rt::Environment environment;

        rt::ObjLoader loader{"./samples/suzanne.obj"};
        environment.Add(std::make_shared<rt::BVHNode>(*loader.Parse(), 0, 1));
        environment.Add(std::make_shared<rt::Sphere>(glm::vec3(0, 6, 6), 4.f,
                                                     std::make_shared<rt::DiffuseLight>(
                                                             std::make_shared<rt::SolidColor>(glm::vec3(2, 2, 2))
                                                     )));

        return rt::Scene{
                rt::Camera(lookFrom, lookAt, vup, 40, aspectRatio, aperture, distToFocus),
                {width, height, channel},
                samplesPerPixel,
                maxDepth,
                {.4, .4, .4},
                environment
        };
    }

    Scene Scene::Denis()
    {
        constexpr float aspectRatio = 16.f / 16.f;

        constexpr uint16_t width           = 500;
        const auto height                  = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 8;
        const uint8_t maxDepth             = 50;

        glm::vec3 lookFrom = glm::vec3{0, 90, 280};
        glm::vec3 lookAt   = glm::vec3{0, 90, 150};
        glm::vec3 vup      = glm::vec3{0., 1., 0.};
        float distToFocus  = 10.f;
        float aperture     = 0.0f;

        rt::Environment environment;

        rt::ObjLoader loader{"./samples/rp_dennis_posed_004_30k.obj"};
        environment.Add(std::make_shared<rt::BVHNode>(*loader.Parse(), 0, 1));
        environment.Add(std::make_shared<rt::Sphere>(glm::vec3(0, 600, 280), 400.f,
                                                     std::make_shared<rt::DiffuseLight>(
                                                             std::make_shared<rt::SolidColor>(glm::vec3(2, 2, 2))
                                                     )));

        return rt::Scene{
                rt::Camera(lookFrom, lookAt, vup, 40, aspectRatio, aperture, distToFocus),
                {width, height, channel},
                samplesPerPixel,
                maxDepth,
                {.4, .4, .4},
                environment
        };
    }
}