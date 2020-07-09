//
// Created by Platholl on 07/07/2020.
//

#ifndef RAYTRACER_ROTATION_HPP
#define RAYTRACER_ROTATION_HPP

#include <glm/gtx/transform.hpp>

#include "Raytracer/Object/Hittable.hpp"

namespace rt
{
    template<uint8_t axis>
    class Rotation : public Hittable
    {
        static_assert(axis < 3, "Axis should be in range of [0, 2]");
    public:
        Rotation(std::shared_ptr<Hittable> object, float angle);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;
    private:
        std::shared_ptr<Hittable> m_object;
        glm::mat4x4 m_rotationMatrix;
        AABB m_boundingBox;
        bool m_haveBoundingBox;
    };
}

#include "Raytracer/Object/Rotation.inl"

#endif //RAYTRACER_ROTATION_HPP
