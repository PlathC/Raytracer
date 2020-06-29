//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_LAMBERTIAN_HPP
#define RAYTRACER_LAMBERTIAN_HPP

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    class Lambertian : public Material
    {
    public:
        Lambertian(const Color& albedo);

        virtual bool Scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override;

    private:
        Color m_albedo;
    };
}

#endif //RAYTRACER_LAMBERTIAN_HPP
