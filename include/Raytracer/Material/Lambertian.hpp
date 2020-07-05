//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_LAMBERTIAN_HPP
#define RAYTRACER_LAMBERTIAN_HPP

#include "Raytracer/Math/Math.hpp"
#include "Raytracer/Material/Material.hpp"

namespace rt
{
    class Lambertian : public Material
    {
    public:
        Lambertian(const glm::vec3& albedo);

        virtual bool Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const override;

    private:
        glm::vec3 m_albedo;
    };
}

#endif //RAYTRACER_LAMBERTIAN_HPP
