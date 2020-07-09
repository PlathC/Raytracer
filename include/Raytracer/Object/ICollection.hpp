//
// Created by Cyprien Plateau--Holleville on 09/07/2020.
//

#ifndef RAYTRACER_ICOLLECTION_HPP
#define RAYTRACER_ICOLLECTION_HPP

#include "Raytracer/Object/IHittable.hpp"

namespace rt
{
    class ICollection : public IHittable
    {
    public:
        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override = 0;
        bool BoundingBox(const double t0, const double t1, AABB& box) const override = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<rt::IHittable>> Objects() const = 0;
        [[nodiscard]] virtual std::size_t Size() const = 0;
        ~ICollection() override = default;
    };
}

#endif //RAYTRACER_ICOLLECTION_HPP
