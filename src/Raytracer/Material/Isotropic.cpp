//
// Created by Platholl on 08/07/2020.
//

#include "Raytracer/Material/Isotropic.hpp"

namespace rt
{
    Isotropic::Isotropic(std::shared_ptr<rt::Texture> albedo):
        m_albedo(albedo)
    {
    }

    bool Isotropic::Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const
    {
        scattered = Ray(record.point, rt::RandomInUnitSphere(), rIn.Time());
        attenuation = m_albedo->Value(record.uv, record.point);

        return true;
    }

}