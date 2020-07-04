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
        Lambertian(const Vec3f& albedo);

        virtual bool Scatter(const Ray& rIn, const HitRecord& record, Vec3f& attenuation, Ray& scattered) const override;

    private:
        Vec3f m_albedo;
    };
}

#endif //RAYTRACER_LAMBERTIAN_HPP
