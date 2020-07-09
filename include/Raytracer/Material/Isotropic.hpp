//
// Created by Platholl on 08/07/2020.
//

#ifndef RAYTRACER_ISOTROPIC_HPP
#define RAYTRACER_ISOTROPIC_HPP

#include "Raytracer/Material/Material.hpp"
#include "Raytracer/Material/Texture.hpp"

namespace rt
{
    class Isotropic : public Material
    {
    public:
        Isotropic(std::shared_ptr<rt::Texture> albedo);

        virtual bool Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const override;
    private:
        std::shared_ptr<rt::Texture> m_albedo;
    };
}

#endif //RAYTRACER_ISOTROPIC_HPP
