//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Object/Sphere.hpp"

#include <glm/gtx/norm.hpp>

namespace rt
{
    Sphere::Sphere(const glm::vec3& center, const float radius, std::unique_ptr<Material>&& material):
        m_center(center),
        m_radius(radius),
        m_material(std::move(material))
    {
    }

    bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        glm::vec3 oc = ray.Origin() - m_center;
        auto a = glm::length2(ray.Direction());
        auto halfB = glm::dot(oc, ray.Direction());
        auto c = glm::length2(oc) - m_radius * m_radius;
        auto discriminant = halfB * halfB - a * c;

        if (discriminant > 0)
        {
            auto root = sqrt(discriminant);
            auto temp = (-halfB - root) / a;
            if (temp < tMax && temp > tMin)
            {
                record.t = temp;
                record.point = ray.At(record.t);
                glm::vec3 outwardNormal = (record.point - m_center) / m_radius;
                record.SetFaceNormal(ray, outwardNormal);
                record.material = m_material.get();
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
                return true;
            }
        }
        return false;
    }
}