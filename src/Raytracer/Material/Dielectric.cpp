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

    bool Dielectric::Scatter(const Ray &rIn, const HitRecord &record, Color &attenuation, Ray &scattered) const
    {
        attenuation = Color(1.0, 1.0, 1.0);
        const double etaiOverEtat = record.frontFace ? 1.0 / m_refraction : m_refraction;

        Vec3 unitDirection = UnitVector(rIn.Direction());

        double cosTheta = std::fmin(Dot(-unitDirection, record.normal), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
        if (etaiOverEtat * sinTheta > 1.0 ) {
            Vec3 reflected = Reflect(unitDirection, record.normal);
            scattered = Ray(record.point, reflected);
            return true;
        }

        double reflectProb = Schlick(cosTheta, etaiOverEtat);
        if (RandomDouble() < reflectProb)
        {
            Vec3 reflected = Reflect(unitDirection, record.normal);
            scattered = Ray(record.point, reflected);
            return true;
        }

        Vec3 refracted = Refract(unitDirection, record.normal, etaiOverEtat);
        scattered = Ray(record.point, refracted);
        return true;
    }
}