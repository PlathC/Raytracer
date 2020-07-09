//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_IHITTABLE_HPP
#define RAYTRACER_IHITTABLE_HPP

#include <memory>

#include <glm/glm.hpp>

#include "Raytracer/Math/Aabb.hpp"
#include "Raytracer/Math/Ray.hpp"

namespace rt
{
    class Material;

    struct HitRecord
    {
        glm::vec3 point;
        glm::vec3 normal;
        float t;
        bool frontFace;
        Material* material;
        glm::vec2 uv;

        inline void SetFaceNormal(const Ray& ray, const glm::vec3& outwardNormal)
        {
            frontFace = glm::dot(ray.Direction(), outwardNormal) < 0;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }
    };

    class IHittable
    {
    public:
        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const = 0;
        virtual ~IHittable() = default;
    };
}

#endif //RAYTRACER_IHITTABLE_HPP
