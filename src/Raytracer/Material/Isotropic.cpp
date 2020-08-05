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

    bool Isotropic::Scatter(const Ray& rIn, const HitRecord& record, ScatterRecord& scatterRecord) const
    {
        scatterRecord.specularRay = Ray(record.point, rt::RandomInUnitSphere(), rIn.Time());
        scatterRecord.albedo = m_albedo->Value(record.uv, record.point);
        scatterRecord.isSpecular = true;
        scatterRecord.pdf = nullptr;
        return true;
    }

}