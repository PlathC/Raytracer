//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "Raytracer/Material/Material.hpp"
#include "Raytracer/Math/Math.hpp"
#include "Raytracer/Object/IHittable.hpp"

namespace rt
{
    class Sphere : public IHittable
    {
    public:
        Sphere() = default;
        Sphere(const glm::vec3& center, const float radius, std::shared_ptr<Material> material);

        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        bool BoundingBox(const double t0, const double t1, AABB& box) const override;

        double PdfValue(const glm::vec3& origin, const glm::vec3& direction) const override;
        glm::vec3 Random(const glm::vec3& origin) const override;

    private:
        glm::vec3 m_center;
        float m_radius;

        std::shared_ptr<Material> m_material;
    };
}

#endif //RAYTRACER_SPHERE_HPP
