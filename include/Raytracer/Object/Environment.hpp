//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_ENVIRONMENT_HPP
#define RAYTRACER_ENVIRONMENT_HPP

#include <memory>
#include <vector>

#include "Raytracer/Object/Hittable.hpp"

namespace rt
{
    class Environment : public Hittable
    {
    public:
        Environment() = default;
        Environment(std::size_t size);

        static Environment RandomEnvironment();
        static Environment TwoSpheres();
        static Environment TwoPerlinSpheres();
        static Environment Earth();
        static Environment SimpleLight();
        static Environment CornellBox();

        void Clear();
        void Add(std::shared_ptr<Hittable> object);

        size_t Size() const;
        std::vector<std::shared_ptr<Hittable>>& Objects();

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;

    private:
        std::vector<std::shared_ptr<Hittable>> m_objects;
    };
}

#endif //RAYTRACER_ENVIRONMENT_HPP
