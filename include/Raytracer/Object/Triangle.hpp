//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_TRIANGLE_HPP
#define RAYTRACER_TRIANGLE_HPP

#include "Raytracer/Object/Hittable.hpp"

namespace rt
{
    class Triangle : public Hittable
    {
    public:
        Triangle(const rt::Vec3& v0, const rt::Vec3& v1, const rt::Vec3& v2, std::unique_ptr<Material>&& material);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
    private:
        rt::Vec3 m_v0, m_v1, m_v2;
        rt::Vec3 m_normal;

        std::unique_ptr<Material> m_material;
    };
}

#endif //RAYTRACER_TRIANGLE_HPP
