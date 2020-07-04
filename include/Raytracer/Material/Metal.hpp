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
        Metal(const Vec3f& albedo, const float fuzziness);

        virtual bool Scatter(const Ray& rIn, const HitRecord& record, Vec3f& attenuation, Ray& scattered) const override;

    private:
        Vec3f m_albedo;
        float m_fuzziness;
    };
}

#endif //RAYTRACER_METAL_HPP
