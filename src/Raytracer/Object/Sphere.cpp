//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Object/Sphere.hpp"

namespace rt
{
    Sphere::Sphere(const Vec3f& center, const float radius, std::unique_ptr<Material>&& material):
        m_center(center),
        m_radius(radius),
        m_material(std::move(material))
    {
    }

    bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        Vec3 oc = ray.Origin() - m_center;
        auto a = ray.Direction().SquaredLength();
        auto halfB = oc.Dot(ray.Direction());
        auto c = oc.SquaredLength() - m_radius * m_radius;
        auto discriminant = halfB * halfB - a * c;

        if (discriminant > 0)
        {
            auto root = sqrt(discriminant);
            auto temp = (-halfB - root) / a;
            if (temp < tMax && temp > tMin)
            {
                record.t = temp;
                record.point = ray.At(record.t);
                Vec3 outwardNormal = (record.point - m_center) / m_radius;
                record.SetFaceNormal(ray, outwardNormal);
                record.material = m_material.get();
                return true;
            }

            temp = (-halfB + root) / a;
            if (temp < tMax && temp > tMin)
            {
                record.t = temp;
                record.point = ray.At(record.t);
                Vec3 outwardNormal = (record.point - m_center) / m_radius;
                record.SetFaceNormal(ray, outwardNormal);
                record.material = m_material.get();
                return true;
            }
        }
        return false;
    }
}