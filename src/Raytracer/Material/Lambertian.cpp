//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Material/Lambertian.hpp"

namespace rt
{
    Lambertian::Lambertian(const Vec3f &albedo) :
        m_albedo(albedo)
    {}

    bool Lambertian::Scatter(const Ray &rIn, const HitRecord &record, Vec3f &attenuation, Ray &scattered) const
    {
        Vec3f scatterDirection = record.normal + RandomUnitVector<float>();
        scattered = Ray(record.point, scatterDirection);
        attenuation = m_albedo;
        return true;
    }
}