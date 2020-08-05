//
// Created by Platholl on 14/07/2020.
//

#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include "Raytracer/Object/Environment.hpp"

#include "Raytracer/Utils/Camera.hpp"

namespace rt
{
    struct Scene
    {
        Camera camera;

        struct ImageSettings
        {
            uint32_t width;
            uint32_t height;
            uint8_t channels;
        } imageSettings;

        uint16_t samplesPerPixel;
        uint8_t maxDepth;

        glm::vec3 backgroundColor;
        rt::Environment environment;
        std::shared_ptr<rt::Environment> lights;

        static Scene RandomEnvironment();
        static Scene TwoSpheres();
        static Scene TwoPerlinSpheres();
        static Scene Earth();
        static Scene SimpleLight();
        static Scene CornellBox();
        static Scene FinalScene();
        static Scene Suzanne();
        static Scene Denis();
    };
}

#endif //RAYTRACER_SCENE_HPP
