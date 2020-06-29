//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Material/Lambertian.hpp"

namespace rt
{
    Lambertian::Lambertian(const Color &albedo) :
        m_albedo(albedo)
    {}

    bool Lambertian::Scatter(const Ray &rIn, const HitRecord &record, Color &attenuation, Ray &scattered) const
    {
        Vec3 scatterDirection = record.normal + RandomUnitVector();
        scattered = Ray(record.point, scatterDirection);
        attenuation = m_albedo;
        return true;
    }
}