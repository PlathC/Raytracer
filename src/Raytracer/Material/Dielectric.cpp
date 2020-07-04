//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Material/Dielectric.hpp"

namespace rt
{
    Dielectric::Dielectric(const double refraction):
            m_refraction(refraction)
    {
    }

    bool Dielectric::Scatter(const Ray &rIn, const HitRecord &record, Vec3f &attenuation, Ray &scattered) const
    {
        attenuation = Vec3f(1.0, 1.0, 1.0);
        const double etaiOverEtat = record.frontFace ? 1.0 / m_refraction : m_refraction;

        Vec3 unitDirection = rIn.Direction().Normalize();

        double cosTheta = std::fmin((-unitDirection).Dot(record.normal), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
        if (etaiOverEtat * sinTheta > 1.0 )
        {
            Vec3 reflected = Reflect(unitDirection, record.normal);
            scattered = Ray(record.point, reflected);
            return true;
        }

        double reflectProb = Schlick(cosTheta, etaiOverEtat);
        if (Random<double>() < reflectProb)
        {
            Vec3 reflected = Reflect(unitDirection, record.normal);
            scattered = Ray(record.point, reflected);
            return true;
        }

        Vec3f refracted = Refract<float>(unitDirection, record.normal, etaiOverEtat);
        scattered = Ray(record.point, refracted);
        return true;
    }
}