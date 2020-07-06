//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_PERLINTEXTURE_HPP
#define RAYTRACER_PERLINTEXTURE_HPP

#include "Raytracer/Material/Texture.hpp"
#include "Raytracer/Math/Perlin.hpp"

namespace rt
{
    class PerlinTexture : public Texture
    {
    public:
        PerlinTexture() = default;
        PerlinTexture(const float scale);

        virtual glm::vec3 Value(const glm::vec2& uv, const glm::vec3& point) const;
    private:
        rt::Perlin m_perlin;
        float m_scale = 1.f;
    };
}

#endif //RAYTRACER_PERLINTEXTURE_HPP
