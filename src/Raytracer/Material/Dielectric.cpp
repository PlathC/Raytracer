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

    bool Dielectric::Scatter(const Ray &rIn, const HitRecord &record, glm::vec3 &albedo, Ray &scattered, double& /*pdf*/) const
    {
        albedo = glm::vec3(1.0, 1.0, 1.0);
        const double etaiOverEtat = record.frontFace ? (1.0 / m_refraction) : m_refraction;

        const glm::vec3 unitDirection = glm::normalize(rIn.Direction());

        const double cosTheta = std::fmin(glm::dot((-unitDirection), record.normal), 1.0);
        const double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
        if (etaiOverEtat * sinTheta > 1.0 )
        {
            glm::vec3 reflected = Reflect(unitDirection, record.normal);
            scattered = Ray(record.point, reflected);
            return true;
        }

        const double reflectProb = Schlick(cosTheta, etaiOverEtat);
        if (Random<double>() < reflectProb)
        {
            glm::vec3 reflected = Reflect(unitDirection, record.normal);
            scattered = Ray(record.point, reflected);
            return true;
        }

        const glm::vec3 refracted = Refract(unitDirection, record.normal, static_cast<float>(etaiOverEtat));
        scattered = Ray(record.point, refracted);
        return true;
    }
}