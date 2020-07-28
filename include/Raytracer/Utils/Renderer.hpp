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
        explicit Renderer(const Scene& settings);

        void GenerateImage();

#ifdef RAYTRACER_WITH_OID
        void Denoise();
#endif //RAYTRACER_WITH_OID

        [[nodiscard]] std::vector<float> GeneratedImage() const;
        [[nodiscard]] std::vector<float> AlbedoImage() const;

#ifdef RAYTRACER_WITH_OID
        [[nodiscard]] std::vector<float> DenoisedImage() const;
#endif //RAYTRACER_WITH_OID

    private:
        [[nodiscard]] glm::vec3 RayColor(const rt::Ray& ray, const rt::IHittable& world, const int depth) const;

    private:
        Scene m_settings;
        BVHNode m_bvh;
        std::vector<float> m_generatedImage;
        std::vector<float> m_albedoImage;
        std::vector<float> m_denoisedImage;
    };
}

#endif //RAYTRACER_RENDERER_HPP
