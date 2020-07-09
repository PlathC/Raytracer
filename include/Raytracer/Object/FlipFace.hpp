//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_FLIPFACE_HPP
#define RAYTRACER_FLIPFACE_HPP

#include "Raytracer/Material/Material.hpp"
#include "Raytracer/Object/IHittable.hpp"

namespace rt
{

    class FlipFace : public IHittable
    {
    public:
        FlipFace(std::shared_ptr<IHittable> object);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;

    private:
        std::shared_ptr<IHittable> m_object;
    };
}


#endif //RAYTRACER_FLIPFACE_HPP
