//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Object/FlipFace.hpp"

namespace rt
{
    FlipFace::FlipFace(std::shared_ptr<IHittable> object):
            m_object(object)
    {
    }

    bool FlipFace::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        if(!m_object->Hit(ray, tMin, tMax, record))
            return false;

        record.frontFace = !record.frontFace;
        return true;
    }

    bool FlipFace::BoundingBox(const double t0, const double t1, AABB &box) const
    {
        return m_object->BoundingBox(t0, t1, box);
    }
}