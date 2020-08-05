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
        Plane(const glm::vec2& v0, const glm::vec2& v1, double weakAxisValue, std::shared_ptr<Material> material);

        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        bool BoundingBox(double t0, double t1, AABB& box) const override;

        double PdfValue(const glm::vec3& /*origin*/, const glm::vec3& /*direction*/) const override;
        glm::vec3 Random(const glm::vec3& /*origin*/) const override;

    private:
        uint8_t m_firstOtherAxis, m_secondOtherAxis;
        glm::vec2 m_v0, m_v1;
        double m_weakAxisValue;
        std::shared_ptr<Material> m_material;
    };

    template<>
    double Plane<1>::PdfValue(const glm::vec3& origin, const glm::vec3& direction) const;

    template<>
    glm::vec3 Plane<1>::Random(const glm::vec3& origin) const;

}

#include "Raytracer/Object/Plane.inl"

#endif //RAYTRACER_PLANE_HPP
