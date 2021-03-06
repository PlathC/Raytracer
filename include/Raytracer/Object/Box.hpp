//
// Created by Platholl on 07/07/2020.
//

#ifndef RAYTRACER_BOX_HPP
#define RAYTRACER_BOX_HPP

#include <vector>

#include "Raytracer/Object/FlipFace.hpp"
#include "Raytracer/Object/IHittable.hpp"
#include "Raytracer/Object/Plane.hpp"

namespace rt
{
    class Box : public IHittable
    {
    public:
        Box() = default;
        Box(const glm::vec3& minimum, const glm::vec3& maximum, std::shared_ptr<Material> material);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;
    private:
        glm::vec3 m_minimum;
        glm::vec3 m_maximum;
        std::shared_ptr<Material> m_material;
        std::vector<std::shared_ptr<IHittable>> m_sides;
    };
}

#endif //RAYTRACER_BOX_HPP
