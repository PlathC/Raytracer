//
// Created by Platholl on 14/07/2020.
//

#include "Raytracer/Utils/Scene.hpp"

namespace rt
{

    Scene Scene::RandomEnvironment()
    {
        constexpr double aspectRatio = 16. / 9.;

        constexpr uint16_t width           = 720;
        const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 50;
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
            Environment::RandomEnvironment()
        };
    }

    Scene Scene::TwoSpheres()
    {
        constexpr double aspectRatio = 16. / 9.;

        constexpr uint16_t width           = 720;
        const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 50;
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
        constexpr double aspectRatio = 16. / 9.;

        constexpr uint16_t width           = 720;
        const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 50;
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
        constexpr double aspectRatio = 16. / 16.;

        constexpr uint16_t width           = 720;
        const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 50;
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
        constexpr double aspectRatio = 16. / 9.;

        constexpr uint16_t width           = 720;
        const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 500;
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
        constexpr double aspectRatio = 16. / 16.;

        constexpr uint16_t width           = 720;
        const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 50;
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
                {1, 1, 1},
                Environment::CornellBox()
        };
    }

    Scene Scene::FinalScene()
    {
        constexpr double aspectRatio = 16. / 16.;

        constexpr uint16_t width           = 720;
        const uint16_t height              = static_cast<uint16_t>(std::floor(width / aspectRatio));
        constexpr uint16_t channel         = 3;
        constexpr uint16_t samplesPerPixel = 50;
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
}