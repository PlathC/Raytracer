//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Object/Triangle.hpp"

#include "Raytracer/Material/Material.hpp"
#include "Raytracer/Math/Core.hpp"

namespace rt
{
    Triangle::Triangle(const rt::Vertex& v0, const rt::Vertex& v1, const rt::Vertex& v2, std::unique_ptr<Material>&& material):
        m_v0(v0),
        m_v1(v1),
        m_v2(v2),
        m_material(std::move(material))
    {
    }

    void Triangle::ComputeNormal()
    {
        glm::vec3 A = m_v1.position - m_v0.position;
        glm::vec3 B = m_v2.position - m_v0.position;
        glm::vec3 normal = glm::cross(A, B);

        // Prefer normalized normals
        if(glm::length(normal) > 0.0)
        {
            normal = glm::normalize(normal);
        }
        m_v0.normal = normal;
        m_v1.normal = normal;
        m_v2.normal = normal;
    }

    bool Triangle::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        // Based on https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution

        const glm::vec3 v0v1 = m_v1.position - m_v0.position;
        const glm::vec3 v0v2 = m_v2.position - m_v0.position;
        const glm::vec3 pVec = glm::cross(ray.Direction(), v0v2);
        const double det = glm::dot(v0v1, pVec);

    #ifdef CULLING
        // if the determinant is negative the triangle is backfacing
        // if the determinant is close to 0, the ray misses the triangle
        if (det < rt::Epsilon) return false;
    #else
        // ray and triangle are parallel if det is close to 0
        if (std::abs(det) < rt::Epsilon) return false;
    #endif

        const double invDet = 1. / det;

        const glm::vec3 tVec = ray.Origin() - m_v0.position;
        const float u = glm::dot(tVec, pVec) * invDet;
        if (u < 0. || u > 1.) return false;

        const glm::vec3 qVec = glm::cross(tVec, v0v1);
        const float v = glm::dot(ray.Direction(), qVec) * invDet;
        if (v < 0. || u + v > 1.) return false;

        const double t = glm::dot(v0v2, qVec) * invDet;

        if (t <= 0.0) // Si distance négative (le triangle se trouve "derrière" le rayon), pas d'intersection
            return false;

        const float w = 1 - (u - v);

        glm::vec3 normal = glm::normalize(w * m_v0.normal
                                        + u * m_v1.normal
                                        + v * m_v2.normal);

        record.t = t;
        record.material = m_material.get();
        record.point = ray.At(t);
        record.SetFaceNormal(ray, normal);

        return true;
    }
}