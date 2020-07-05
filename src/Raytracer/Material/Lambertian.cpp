//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Material/Lambertian.hpp"

namespace rt
{
    Lambertian::Lambertian(const glm::vec3& albedo) :
        m_albedo(albedo)
    {}

    bool Lambertian::Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const
    {
        glm::vec3 scatterDirection = record.normal + RandomUnitVector<float>();
        scattered = Ray(record.point, scatterDirection, rIn.Time());
        attenuation = m_albedo;
        return true;
    }
}