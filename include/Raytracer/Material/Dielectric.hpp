//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_DIELECTRIC_HPP
#define RAYTRACER_DIELECTRIC_HPP

#include "Raytracer/Math/Math.hpp"
#include "Raytracer/Material/Material.hpp"

namespace rt
{
    class Dielectric : public Material
    {
    public:
        Dielectric(const double refraction);

        bool Scatter(const Ray& rIn, const HitRecord& record, ScatterRecord& scatterRecord) const override;

    private:
        double m_refraction;
    };
}

#endif //RAYTRACER_DIELECTRIC_HPP
