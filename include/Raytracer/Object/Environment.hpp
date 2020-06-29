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

        void Clear();
        void Add(std::unique_ptr<Hittable>&& object);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
    private:
        std::vector<std::unique_ptr<Hittable>> m_objects;
    };
}

#endif //RAYTRACER_ENVIRONMENT_HPP
