//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_METAL_HPP
#define RAYTRACER_METAL_HPP

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    class Metal : public Material
    {
    public:
        Metal(const Color& albedo, const double fuzziness);

        virtual bool Scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

    private:
        Color m_albedo;
        double m_fuzziness;
    };
}

#endif //RAYTRACER_METAL_HPP
