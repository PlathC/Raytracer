//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Object/Triangle.hpp"

#include "Raytracer/Material/Material.hpp"
#include "Raytracer/Math/Math.hpp"

namespace rt
{
    Triangle::Triangle(const rt::Vertex& v0, const rt::Vertex& v1, const rt::Vertex& v2, std::shared_ptr<Material> material):
        m_v0(v0),
        m_v1(v1),
        m_v2(v2),
        m_material(material)
    {
    }

    void Triangle::ComputeNormal(rt::Vertex& v0, rt::Vertex& v1, rt::Vertex& v2)
    {
        glm::vec3 A = v1.position - v0.position;
        glm::vec3 B = v2.position - v0.position;
        glm::vec3 normal = glm::cross(A, B);

        // Prefer normalized normals
        v0.normal += normal;
        v1.normal += normal;
        v2.normal += normal;
    }

    bool Triangle::Hit(const Ray& ray, double /*tMin*/, double /*tMax*/, HitRecord& record) const
    {
        // Based on https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution

        const glm::vec3 v0v1 = m_v1.position - m_v0.position;
        const glm::vec3 v0v2 = m_v2.position - m_v0.position;
        const glm::vec3 pVec = glm::cross(ray.Direction(), v0v2);
        const float det = glm::dot(v0v1, pVec);

    #ifndef CULLING
        // if the determinant is negative the triangle is backfacing
        // if the determinant is close to 0, the ray misses the triangle
        if (det < rt::Epsilon<float>) return false;
    #else
        // ray and triangle are parallel if det is close to 0
        if (std::fabs(det) < rt::Epsilon<float>) return false;
    #endif

        const float invDet = 1.f / det;

        const glm::vec3 tVec = ray.Origin() - m_v0.position;
        const auto u = static_cast<float>(glm::dot(tVec, pVec)) * invDet;
        if (u < 0. || u > 1.) return false;

        const glm::vec3 qVec = glm::cross(tVec, v0v1);
        const auto v = static_cast<float>(glm::dot(ray.Direction(), qVec)) * invDet;
        if (v < 0. || u + v > 1.) return false;

        const auto t = static_cast<float>(glm::dot(v0v2, qVec)) * invDet;

        if (t <= 0.f)
            return false;

        const float w = 1.f - u - v;

        if(t < 0) return false;

        glm::vec3 normal = glm::normalize(w * m_v0.normal
                                        + u * m_v1.normal
                                        + v * m_v2.normal);

        record.t = t;
        record.material = m_material.get();
        record.point = ray.At(t);
        record.SetFaceNormal(ray, normal);
        record.uv = glm::vec2(u, v);

        return true;
    }

    bool Triangle::BoundingBox(const double /*t0*/, const double /*t1*/, AABB& box) const
    {
        glm::vec3 min = {
                std::min(m_v0.position.x, m_v1.position.x),
                std::min(m_v0.position.y, m_v1.position.y),
                std::min(m_v0.position.z, m_v1.position.z)
        };

        min = glm::vec3{
                std::min(min.x, m_v2.position.x),
                std::min(min.y, m_v2.position.y),
                std::min(min.z, m_v2.position.z)
        };


        glm::vec3 max = {
                std::max(m_v0.position.x, m_v1.position.x),
                std::max(m_v0.position.y, m_v1.position.y),
                std::max(m_v0.position.z, m_v1.position.z)
        };

        max = glm::vec3{
                std::max(max.x, m_v2.position.x),
                std::max(max.y, m_v2.position.y),
                std::max(max.z, m_v2.position.z)
        };
        box = AABB(min, max);
        return true;
    }
}