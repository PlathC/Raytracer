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
        explicit DiffuseLight(std::shared_ptr<rt::Texture> texture);

        [[nodiscard]] glm::vec3 Emitted(const Ray& rIn, const HitRecord& record) const override;
    private:
        // TODO : Make a difference between texture color and light intensity.
        std::shared_ptr<rt::Texture> m_texture;
    };
}

#endif //RAYTRACER_DIFFUSELIGHT_HPP
