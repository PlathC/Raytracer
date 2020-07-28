//
// Created by Platholl on 07/07/2020.
//

#include "Raytracer/Object/Box.hpp"

namespace rt
{
    Box::Box(const glm::vec3& minimum, const glm::vec3& maximum, std::shared_ptr<Material> material):
        m_minimum(minimum),
        m_maximum(maximum),
        m_material(material)
    {
        m_sides.reserve(6);
        m_sides.emplace_back(std::make_unique<rt::Plane<2>>(
                glm::vec2(m_minimum.x, m_minimum.y),
                glm::vec2(m_maximum.x, m_maximum.y),
                m_maximum.z,
                nullptr
        ));

        m_sides.emplace_back(std::make_unique<rt::FlipFace>(std::make_unique<rt::Plane<2>>(
                glm::vec2(m_minimum.x, m_minimum.y),
                glm::vec2(m_maximum.x, m_maximum.y),
                m_minimum.z,
                nullptr
        )));

        m_sides.emplace_back(std::make_unique<rt::Plane<1>>(
                glm::vec2(m_minimum.x, m_minimum.z),
                glm::vec2(m_maximum.x, m_maximum.z),
                m_maximum.y,
                nullptr
        ));
        m_sides.emplace_back(std::make_unique<rt::FlipFace>(std::make_unique<rt::Plane<1>>(
                glm::vec2(m_minimum.x, m_minimum.z),
                glm::vec2(m_maximum.x, m_maximum.z),
                m_minimum.y,
                nullptr
        )));

        m_sides.emplace_back(std::make_unique<rt::Plane<0>>(
                glm::vec2(m_minimum.y, m_minimum.z),
                glm::vec2(m_maximum.y, m_maximum.z),
                m_maximum.x,
                nullptr
        ));
        m_sides.emplace_back(std::make_unique<rt::FlipFace>(std::make_unique<rt::Plane<0>>(
                glm::vec2(m_minimum.y, m_minimum.z),
                glm::vec2(m_maximum.y, m_maximum.z),
                m_minimum.x,
                nullptr
        )));
    }

    bool Box::Hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const
    {
        HitRecord tempRecord;
        bool hitAnything = false;
        auto closestSoFar = tMax;

        for (const auto& object : m_sides)
        {
            if (object->Hit(ray, tMin, closestSoFar, tempRecord))
            {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                record = tempRecord;
            }
        }

        if(hitAnything)
            record.material = m_material.get();

        return hitAnything;
    }

    bool Box::BoundingBox(const double /*t0*/, const double /*t1*/, AABB& box) const
    {
        box = AABB(m_minimum, m_maximum);
        return true;
    }
}