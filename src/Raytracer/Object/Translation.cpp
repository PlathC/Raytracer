//
// Created by Platholl on 07/07/2020.
//

#include "Raytracer/Object/Translation.hpp"

namespace rt
{
    Translation::Translation(std::shared_ptr<IHittable> object, const glm::vec3& movement):
        m_object(object),
        m_movement(movement)
    {
    }

    bool Translation::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        Ray movedRay = Ray{
            ray.Origin() - m_movement,
            ray.Direction(),
            ray.Time()
        };
        if(!m_object->Hit(movedRay, tMin, tMax, record))
            return false;

        record.point += m_movement;
        record.SetFaceNormal(movedRay, record.normal);

        return true;
    }

    bool Translation::BoundingBox(const double t0, const double t1, AABB& box) const
    {
        if(!m_object->BoundingBox(t0, t1, box))
            return false;

        box = AABB(
                box.Minimum() + m_movement,
                box.Maximum() + m_movement);

        return true;
    }
}