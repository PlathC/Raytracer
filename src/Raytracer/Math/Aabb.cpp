//
// Created by Platholl on 05/07/2020.
//

#include "Raytracer/Math/Aabb.hpp"

namespace rt
{
    AABB::AABB(const glm::vec3& minimum, const glm::vec3& maximum):
        m_minimum(minimum),
        m_maximum(maximum)
    {
    }

    AABB::AABB(const AABB& fBox, const AABB& sBox):
        m_minimum(std::fmin(fBox.m_minimum.x, sBox.m_minimum.x),
                  std::fmin(fBox.m_minimum.y, sBox.m_minimum.y),
                  std::fmin(fBox.m_minimum.z, sBox.m_minimum.z)),
        m_maximum(std::fmax(fBox.m_maximum.x, sBox.m_maximum.x),
                  std::fmax(fBox.m_maximum.y, sBox.m_maximum.y),
                  std::fmax(fBox.m_maximum.z, sBox.m_maximum.z))
    {
    }

    glm::vec3 AABB::Minimum() const
    {
        return m_minimum;
    }

    glm::vec3 AABB::Maximum() const
    {
        return m_maximum;
    }

    bool AABB::Hit(const rt::Ray& ray, double tMin, double tMax) const
    {
        // Andrew Kensler AABB hit method
        for(uint8_t c = 0; c < 3; c++)
        {
            float invDirection = 1.f / ray.Direction()[c];
            float t0 = (m_minimum[c] - ray.Origin()[c]) * invDirection;
            float t1 = (m_maximum[c] - ray.Origin()[c]) * invDirection;

            if(invDirection < 0.f)
                std::swap(t0, t1);

            tMin = t0 > tMin ? t0 : tMin;
            tMax = t1 < tMax ? t1 : tMax;

            if(tMax <= tMin)
            {
                return false;
            }
        }

        return true;
    }
}