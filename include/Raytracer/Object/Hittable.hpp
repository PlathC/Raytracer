//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include <memory>

#include <glm/glm.hpp>

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

    class Hittable
    {
    public:
        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
        virtual ~Hittable() {};
    };
}

#endif //RAYTRACER_HITTABLE_HPP
