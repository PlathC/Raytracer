//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include <glm/glm.hpp>

#include "Raytracer/Math/Ray.hpp"
#include "Raytracer/Object/Hittable.hpp"

namespace rt
{
    class Material
    {
    public:
        virtual bool Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const = 0;
        virtual ~Material() { };
    };
}

#endif //RAYTRACER_MATERIAL_HPP
