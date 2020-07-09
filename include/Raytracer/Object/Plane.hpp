//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_PLANE_HPP
#define RAYTRACER_PLANE_HPP

#include "Raytracer/Object/IHittable.hpp"

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    template<uint8_t weakAxis>
    class Plane : public IHittable
    {
        static_assert(weakAxis < 3, "Axis should be in range of [0, 2].");
    public:
        Plane() = default;
        Plane(const glm::vec2& v0, const glm::vec2& v1, const double weakAxisValue, std::shared_ptr<Material> material);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const;

    private:
        uint8_t m_firstOtherAxis, m_secondOtherAxis;
        glm::vec2 m_v0, m_v1;
        double m_weakAxisValue;
        std::shared_ptr<Material> m_material;
    };
}

#include "Raytracer/Object/Plane.inl"

#endif //RAYTRACER_PLANE_HPP
