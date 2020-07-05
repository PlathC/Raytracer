//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_TRIANGLE_HPP
#define RAYTRACER_TRIANGLE_HPP

#include "Raytracer/Object/Hittable.hpp"
#include "Raytracer/Object/Vertex.hpp"

namespace rt
{
    class Triangle : public Hittable
    {
    public:
        Triangle(const rt::Vertex& v0, const rt::Vertex& v1, const rt::Vertex& v2, std::unique_ptr<Material>&& material = {});

        void ComputeNormal();

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;

    private:
        rt::Vertex m_v0, m_v1, m_v2;

        std::unique_ptr<Material> m_material;
    };
}

#endif //RAYTRACER_TRIANGLE_HPP
