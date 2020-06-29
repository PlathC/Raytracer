//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "Raytracer/Object/Hittable.hpp"

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    class Sphere : public Hittable
    {
    public:
        Sphere() = default;
        Sphere(const Point3& center, const double radius, std::unique_ptr<Material>&& material);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

    private:
        Point3 m_center;
        double m_radius;

        std::unique_ptr<Material> m_material;
    };
}

#endif //RAYTRACER_SPHERE_HPP
