//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include <glm/glm.hpp>

#include "Raytracer/Math/ProbabilityDensityFunction.hpp"
#include "Raytracer/Math/Ray.hpp"
#include "Raytracer/Object/IHittable.hpp"

namespace rt
{
    struct ScatterRecord
    {
        Ray specularRay;
        bool isSpecular;
        glm::vec3 albedo;
        std::shared_ptr<ProbabilityDensityFunction> pdf;
    };

    class Material
    {
    public:
        virtual bool Scatter(const Ray& rIn, const HitRecord& record, ScatterRecord& sRecord) const;
        virtual double ScatteringPdf(const Ray& rIn, const HitRecord& record, Ray& scattered) const;
        virtual glm::vec3 Emitted(const Ray& rIn, const HitRecord& record) const;
        virtual ~Material() { };
    };
}

#endif //RAYTRACER_MATERIAL_HPP
