//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_SOLIDCOLOR_HPP
#define RAYTRACER_SOLIDCOLOR_HPP

#include "Raytracer/Material/Texture.hpp"

namespace rt
{
    class SolidColor : public Texture
    {
    public:
        SolidColor() = default;
        SolidColor(const glm::vec3& color);

        virtual glm::vec3 Value(const glm::vec2& uv, const glm::vec3& point) const override;

        virtual ~SolidColor() = default;
    private:
        glm::vec3 m_color;
    };
}

#endif //RAYTRACER_SOLIDCOLOR_HPP
