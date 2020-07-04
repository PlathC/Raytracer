//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include <memory>

#include "Raytracer/Math/Vec.hpp"
#include "Raytracer/Math/Ray.hpp"


namespace rt
{
    class Material;

    struct HitRecord
    {
        Vec3f point;
        Vec3f normal;
        float t;
        bool frontFace;
        Material* material;

        inline void SetFaceNormal(const Ray& ray, const Vec3f& outwardNormal)
        {
            frontFace = ray.Direction().Dot(outwardNormal) < 0;
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
