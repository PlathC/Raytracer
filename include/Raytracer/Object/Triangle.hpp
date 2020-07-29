//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_TRIANGLE_HPP
#define RAYTRACER_TRIANGLE_HPP

#include "Raytracer/Object/IHittable.hpp"
#include "Raytracer/Object/Vertex.hpp"

namespace rt
{
    class Triangle : public IHittable
    {
    public:
        Triangle(const rt::Vertex& v0, const rt::Vertex& v1, const rt::Vertex& v2, std::shared_ptr<Material> material);

        static void ComputeNormal(rt::Vertex& v0, rt::Vertex& v1, rt::Vertex& v2);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;

    private:
        rt::Vertex m_v0;
        rt::Vertex m_v1;
        rt::Vertex m_v2;

        glm::vec3 m_min;
        glm::vec3 m_max;

        std::shared_ptr<Material> m_material;
    };
}

#endif //RAYTRACER_TRIANGLE_HPP
