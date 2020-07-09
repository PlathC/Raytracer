//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_ENVIRONMENT_HPP
#define RAYTRACER_ENVIRONMENT_HPP

#include <memory>
#include <vector>

#include "Raytracer/Object/ICollection.hpp"

namespace rt
{
    class Environment : public ICollection
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
        static Environment FinalScene();

        void Clear();
        void Add(std::shared_ptr<IHittable> object);

        [[nodiscard]] size_t Size() const override;
        [[nodiscard]] std::vector<std::shared_ptr<IHittable>> Objects() const override;

        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        bool BoundingBox(const double t0, const double t1, AABB& box) const override;

    protected:
        std::vector<std::shared_ptr<IHittable>> m_objects;
    };
}

#endif //RAYTRACER_ENVIRONMENT_HPP
