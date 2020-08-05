//
// Created by Platholl on 05/08/2020.
//

#include "Raytracer/Object/Plane.hpp"

namespace rt
{
    template<>
    double Plane<1>::PdfValue(const glm::vec3& origin, const glm::vec3& direction) const
    {
        HitRecord record;
        if(!Hit(Ray(origin, direction), 0.001, rt::Infinity<double>, record))
            return 0;

        float area = (m_v1.x - m_v0.x) * (m_v1.y - m_v0.y);
        float distanceSquared = record.t * record.t * glm::length2(direction);
        float cosine = std::fabs(glm::dot(direction, record.normal) / glm::length(direction));

        return distanceSquared / (cosine * area);
    }

    template<>
    glm::vec3 Plane<1>::Random(const glm::vec3& origin) const
    {
        glm::vec3 randomPoint {};

        randomPoint[1] = m_weakAxisValue;
        float minValue = std::min(m_v0.x, m_v1.x);
        float maxValue = std::max(m_v0.x, m_v1.x);
        randomPoint[0] = rt::Random(minValue, maxValue);

        minValue = std::min(m_v0.y, m_v1.y);
        maxValue = std::max(m_v0.y, m_v1.y);
        randomPoint[2] = rt::Random(minValue, maxValue);

        return randomPoint - origin;
    }
}