//
// Created by Platholl on 28/06/2020.
//

#include <glm/gtx/norm.hpp>

#include "Raytracer/Object/Sphere.hpp"

namespace rt
{
    Sphere::Sphere(const glm::vec3& center, const float radius, std::shared_ptr<Material> material):
        m_center(center),
        m_radius(radius),
        m_material(material)
    {
    }

    bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        glm::vec3 oc = ray.Origin() - m_center;
        auto a = glm::length2(ray.Direction());
        auto halfB = glm::dot(oc, ray.Direction());
        auto c = glm::length2(oc) - m_radius * m_radius;
        auto discriminant = halfB * halfB - a * c;

        auto ComputeUV = [](const glm::vec3& point) -> glm::vec2
        {
            double phi = std::atan2(point.z, point.x);
            double theta = std::asin(point.y);
            return glm::vec2{
                1 - (phi + rt::Pi) / (2 * rt::Pi),
                (theta + rt::Pi / 2.f) / rt::Pi
            };
        };

        if (discriminant > 0)
        {
            auto root = std::sqrt(discriminant);
            auto temp = (-halfB - root) / a;
            if (temp < tMax && temp > tMin)
            {
                record.t = temp;
                record.point = ray.At(record.t);
                glm::vec3 outwardNormal = (record.point - m_center) / m_radius;
                record.SetFaceNormal(ray, outwardNormal);
                record.material = m_material.get();
                record.uv = ComputeUV(outwardNormal);
                return true;
            }

            temp = (-halfB + root) / a;
            if (temp < tMax && temp > tMin)
            {
                record.t = temp;
                record.point = ray.At(record.t);
                glm::vec3 outwardNormal = (record.point - m_center) / m_radius;
                record.SetFaceNormal(ray, outwardNormal);
                record.material = m_material.get();
                record.uv = ComputeUV(outwardNormal);
                return true;
            }
        }
        return false;
    }

    bool Sphere::BoundingBox(const double /*t0*/, const double /*t1*/, AABB& box) const
    {
        box = AABB{m_center - glm::vec3(m_radius, m_radius, m_radius),
                   m_center + glm::vec3(m_radius, m_radius, m_radius)};
        return true;
    }

    double Sphere::PdfValue(const glm::vec3& origin, const glm::vec3& direction) const
    {
        HitRecord record{};
        if(!Hit(Ray(origin, direction), 0.001, rt::Infinity<double>, record))
            return 0;

        float cosThetaMax = std::sqrt(1 - m_radius * m_radius / glm::length2(m_center - origin));
        float solidAngle  = 2 * rt::Pi * (1 - cosThetaMax);

        return 1 / solidAngle;
    }

    glm::vec3 Sphere::Random(const glm::vec3& origin) const
    {
        glm::vec3 direction = m_center - origin;
        float distanceSQuared = glm::length2(direction);
        OrthonormalBase base;
        base.BuildFromW(direction);
        return base.Local(rt::RandomToSphere(m_radius, distanceSQuared));
    }
}