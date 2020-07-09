//
// Created by Platholl on 08/07/2020.
//

#ifndef RAYTRACER_CONSTANTDENSITYMEDIUM_HPP
#define RAYTRACER_CONSTANTDENSITYMEDIUM_HPP

#include "Raytracer/Material/Texture.hpp"
#include "Raytracer/Material/Isotropic.hpp"
#include "Raytracer/Object/IHittable.hpp"

namespace rt
{
    class ConstantDensityMedium : public IHittable
    {
    public:
        ConstantDensityMedium(std::shared_ptr<rt::IHittable> boundary, std::shared_ptr<rt::Texture> material,
                double density);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;

    private:
        std::shared_ptr<rt::IHittable> m_boundary;
        std::shared_ptr<rt::Material> m_phaseFunction;
        double m_negativeInverseDensity;
    };
}


#endif //RAYTRACER_CONSTANTDENSITYMEDIUM_HPP
