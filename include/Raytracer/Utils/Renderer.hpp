//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_RENDERER_HPP
#define RAYTRACER_RENDERER_HPP

#include "Raytracer/Core/ThreadPool.hpp"

#include "Raytracer/Object/BvhNode.hpp"
#include "Raytracer/Object/Sphere.hpp"

#include "Raytracer/Utils/Scene.hpp"

namespace rt
{

    class Renderer
    {
    public:
        Renderer(const Scene& settings);

        std::vector<float> GenerateImage();

    private:
        glm::vec3 RayColor(const rt::Ray& ray, const rt::IHittable& world, const int depth) const;

    private:
        Scene m_settings;
        BVHNode m_bvh;
    };
}

#endif //RAYTRACER_RENDERER_HPP
