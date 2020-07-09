//
// Created by Platholl on 05/07/2020.
//

#include "Raytracer/Object/MovingSphere.hpp"

#include <glm/gtx/norm.hpp>

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    MovingSphere::MovingSphere(const glm::vec3& center0, const glm::vec3& center1, const float t0, const float t1,
            const float radius, std::shared_ptr<Material> material):
            m_center0(center0),
            m_center1(center1),
            m_time0(t0),
            m_time1(t1),
            m_radius(radius),
            m_material(material)
    {
    }

    bool MovingSphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        glm::vec3 oc = ray.Origin() - Center(ray.Time());
        auto a = glm::length2(ray.Direction());
        auto halfB = glm::dot(oc, ray.Direction());
        auto c = glm::length2(oc) - m_radius * m_radius;
        auto discriminant = halfB * halfB - a * c;

        if (discriminant > 0)
        {
            auto root = std::sqrt(discriminant);
            auto temp = (-halfB - root) / a;
            if (temp < tMax && temp > tMin)
            {
                record.t = temp;
                record.point = ray.At(record.t);
                glm::vec3 outwardNormal = (record.point - Center(ray.Time())) / m_radius;
                record.SetFaceNormal(ray, outwardNormal);
                record.material = m_material.get();
                return true;
            }

            temp = (-halfB + root) / a;
            if (temp < tMax && temp > tMin)
            {
                record.t = temp;
                record.point = ray.At(record.t);
                glm::vec3 outwardNormal = (record.point - Center(ray.Time())) / m_radius;
                record.SetFaceNormal(ray, outwardNormal);
                record.material = m_material.get();
                return true;
            }
        }
        return false;
    }

    bool MovingSphere::BoundingBox(const double t0, const double t1, AABB& box) const
    {
        AABB box0 = AABB{m_center0 - glm::vec3(m_radius, m_radius, m_radius),
                         m_center0 + glm::vec3(m_radius, m_radius, m_radius)};

        AABB box1 = AABB{m_center1 - glm::vec3(m_radius, m_radius, m_radius),
                         m_center1 + glm::vec3(m_radius, m_radius, m_radius)};

        box = AABB(box0, box1);

        return true;
    }

    glm::vec3 MovingSphere::Center(const float time) const
    {
        // Simple linear center interpolation
        return m_center0 + ((time - m_time0) / (m_time1 - m_time0)) * (m_center1 - m_center0);
    }
}