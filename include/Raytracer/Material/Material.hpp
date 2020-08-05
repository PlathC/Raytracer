//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include <glm/glm.hpp>

#include "Raytracer/Math/Ray.hpp"
#include "Raytracer/Object/IHittable.hpp"

namespace rt
{
    class Material
    {
    public:
        virtual bool Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& albedo, Ray& scattered, double& pdf) const;
        virtual double ScatteringPdf(const Ray& rIn, const HitRecord& record, Ray& scattered) const;
        virtual glm::vec3 Emitted(const Ray& rIn, const HitRecord& record) const;
        virtual ~Material() { };
    };
}

#endif //RAYTRACER_MATERIAL_HPP
