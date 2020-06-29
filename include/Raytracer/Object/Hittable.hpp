//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include <memory>

#include "Raytracer/Math/Vec3.hpp"
#include "Raytracer/Math/Ray.hpp"


namespace rt
{
    class Material;

    struct HitRecord
    {
        Point3 point;
        Vec3 normal;
        double t;
        bool frontFace;
        Material* material;

        inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal)
        {
            frontFace = Dot(ray.Direction(), outwardNormal) < 0;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }
    };

    class Hittable
    {
    public:
        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
    };
}

#endif //RAYTRACER_HITTABLE_HPP
