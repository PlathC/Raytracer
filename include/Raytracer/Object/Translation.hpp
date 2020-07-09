//
// Created by Platholl on 07/07/2020.
//

#ifndef RAYTRACER_TRANSLATION_HPP
#define RAYTRACER_TRANSLATION_HPP

#include "Raytracer/Object/IHittable.hpp"

namespace rt
{
    class Translation : public IHittable
    {
    public:
        Translation(std::shared_ptr<IHittable> object, const glm::vec3& movement);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;
    private:
        std::shared_ptr<IHittable> m_object;
        glm::vec3 m_movement;
    };
}

#endif //RAYTRACER_TRANSLATION_HPP
