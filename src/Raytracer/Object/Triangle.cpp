//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Object/Triangle.hpp"

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    Triangle::Triangle(const rt::Vec3& v0, const rt::Vec3& v1, const rt::Vec3& v2, std::unique_ptr<Material>&& material):
            m_v0(v0),
            m_v1(v1),
            m_v2(v2),
            m_material(std::move(material))
    {
        rt::Vec3 A = m_v1 - m_v0;
        rt::Vec3 B = m_v2 - m_v0;
        m_normal = Cross(A, B);

        // Prefer normalized normals
        if(m_normal.Length() > 0.0)
        {
            m_normal = UnitVector(m_normal);
        }
    }

    Triangle::Triangle(const rt::Vec3& v0, const rt::Vec3& v1, const rt::Vec3& v2, const rt::Vec3& normal,
                       std::unique_ptr<Material>&& material):
            m_v0(v0),
            m_v1(v1),
            m_v2(v2),
            m_normal(normal),
            m_material(std::move(material))
    {
    }

    bool Triangle::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        // Based on https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution

        const Vec3 v0v1 = m_v1 - m_v0;
        const Vec3 v0v2 = m_v2 - m_v0;
        const Vec3 pVec = Cross(ray.Direction(), v0v2);
        const double det = Dot(v0v1, pVec);

    #ifdef CULLING
        // if the determinant is negative the triangle is backfacing
        // if the determinant is close to 0, the ray misses the triangle
        if (det < rt::Epsilon) return false;
    #else
        // ray and triangle are parallel if det is close to 0
        if (std::abs(det) < rt::Epsilon) return false;
    #endif

        const double invDet = 1. / det;

        const Vec3 tVec = ray.Origin() - m_v0;
        const double u = Dot(tVec, pVec) * invDet;
        if (u < 0.0 || u > 1.0) return false;

        const Vec3 qVec = Cross(tVec, v0v1);
        const double v = Dot(ray.Direction(), qVec) * invDet;
        if (v < 0.0 || u + v > 1.0) return false;

        const double t = Dot(v0v2, qVec) * invDet;

        record.t = t;
        record.material = m_material.get();
        record.point = ray.At(t);
        record.SetFaceNormal(ray, m_normal);

        return true;
    }
}