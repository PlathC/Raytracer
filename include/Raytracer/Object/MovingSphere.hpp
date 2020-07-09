//
// Created by Platholl on 05/07/2020.
//

#ifndef RAYTRACER_MOVINGSPHERE_HPP
#define RAYTRACER_MOVINGSPHERE_HPP

#include "Raytracer/Object/IHittable.hpp"

namespace rt
{
    class MovingSphere : public IHittable
    {
    public:
        MovingSphere() = default;
        MovingSphere(const glm::vec3& center0, const glm::vec3& center1, const float t0, const float t1,
                const float radius, std::shared_ptr<Material> material);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;

        glm::vec3 Center(const float time) const;

        ~MovingSphere() = default;
    private:
        glm::vec3 m_center0;
        glm::vec3 m_center1;

        float m_time0;
        float m_time1;
        float m_radius;
        std::shared_ptr<Material> m_material;
    };
}

#endif //RAYTRACER_MOVINGSPHERE_HPP
