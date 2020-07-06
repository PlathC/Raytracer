//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_DIFFUSELIGHT_HPP
#define RAYTRACER_DIFFUSELIGHT_HPP

#include "Raytracer/Material/Material.hpp"
#include "Raytracer/Material/Texture.hpp"

namespace rt
{
    class DiffuseLight : public Material
    {
    public:
        DiffuseLight(std::unique_ptr<rt::Texture> texture);

        virtual bool Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const override;

        virtual glm::vec3 Emitted(const glm::vec2& uv, const glm::vec3& point) const override;
    private:
        // TODO : Make a difference between texture color and light intensity.
        std::unique_ptr<rt::Texture> m_texture;
    };
}

#endif //RAYTRACER_DIFFUSELIGHT_HPP
