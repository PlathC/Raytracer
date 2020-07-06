//
// Created by Platholl on 06/07/2020.
//


#include "Raytracer/Math/Core.hpp"

namespace rt
{
    template<uint8_t weakAxis>
    Plane<weakAxis>::Plane(const glm::vec2& v0, const glm::vec2& v1, const double weakAxisValue, std::unique_ptr<Material> material):
        m_v0(v0),
        m_v1(v1),
        m_weakAxisValue(weakAxisValue),
        m_material(std::move(material))
    {
        if constexpr (weakAxis == 0)
        {
            m_firstOtherAxis  = 1;
            m_secondOtherAxis = 2;
        }
        else if constexpr (weakAxis == 1)
        {
            m_firstOtherAxis = 0;
            m_secondOtherAxis = 2;
        }
        else if constexpr (weakAxis == 2)
        {
            m_firstOtherAxis = 0;
            m_secondOtherAxis = 1;
        }
    }

    template<uint8_t weakAxis>
    bool Plane<weakAxis>::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        // Finding t based on z value
        float t = (m_weakAxisValue - ray.Origin()[weakAxis]) / ray.Direction()[weakAxis];
        if(t < tMin || t > tMax)
            return false;

        // Find x and y based on computed t
        float firstOtherAxisValue  = ray.Origin()[m_firstOtherAxis]  + t * ray.Direction()[m_firstOtherAxis];
        float secondOtherAxisValue = ray.Origin()[m_secondOtherAxis] + t * ray.Direction()[m_secondOtherAxis];

        // Outside of the 2D plane
        if(firstOtherAxisValue < m_v0.x || firstOtherAxisValue > m_v1.x
        || secondOtherAxisValue < m_v0.y || secondOtherAxisValue > m_v1.y)
            return false;

        record.uv = glm::vec2{
                (firstOtherAxisValue - m_v0.x) / (m_v1.x - m_v0.x),
                (secondOtherAxisValue - m_v0.y) / (m_v1.y - m_v0.y)
        };

        record.t = t;

        auto normal = glm::vec3(0, 0, 0);
        normal[weakAxis] = 1;
        record.SetFaceNormal(ray, normal);
        record.material = m_material.get();
        record.point = ray.At(t);

        return true;
    }

    template<uint8_t weakAxis>
    bool Plane<weakAxis>::BoundingBox(const double t0, const double t1, AABB& box) const
    {
        auto firstValue = glm::vec3();
        firstValue[weakAxis] = m_weakAxisValue - 0.0001;
        firstValue[m_firstOtherAxis] = m_v0.x;
        firstValue[m_secondOtherAxis] = m_v0.y;

        auto secondValue = glm::vec3();
        secondValue[weakAxis] = m_weakAxisValue + 0.0001;
        secondValue[m_firstOtherAxis] = m_v1.x;
        secondValue[m_secondOtherAxis] = m_v1.y;
        box = AABB(firstValue, secondValue);
        return true;
    }
}