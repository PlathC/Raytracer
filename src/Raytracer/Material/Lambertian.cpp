//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Material/Lambertian.hpp"

namespace rt
{
    Lambertian::Lambertian(std::unique_ptr<Texture> albedo) :
        m_albedo(std::move(albedo))
    {}

    bool Lambertian::Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const
    {
        glm::vec3 scatterDirection = record.normal + RandomInUnitSphere<float>();
        scattered = Ray(record.point, scatterDirection, rIn.Time());
        attenuation = m_albedo->Value(record.uv, record.point);
        return true;
    }
}