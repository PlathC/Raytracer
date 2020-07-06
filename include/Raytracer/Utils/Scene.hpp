//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include "Raytracer/Object/BvhNode.hpp"
#include "Raytracer/Object/Environment.hpp"
#include "Raytracer/Object/Sphere.hpp"

#include "Raytracer/Utils/Camera.hpp"

namespace rt
{
    struct SceneSettings
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
    };

    class Scene
    {
    public:
        Scene(const SceneSettings& settings, Environment environment);

        std::vector<uint8_t> GenerateImage();

    private:
        glm::vec3 RayColor(const rt::Ray& ray, const rt::Hittable& world, const int depth) const;

    private:
        SceneSettings m_settings;
        Environment m_environment;
        BVHNode m_bvh;
    };
}

#endif //RAYTRACER_SCENE_HPP
