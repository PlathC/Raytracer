//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Material/SolidColor.hpp"

namespace rt
{
    SolidColor::SolidColor(const glm::vec3 &color):
        m_color(color)
    {}

    glm::vec3 SolidColor::Value(const glm::vec2& /*uv*/, const glm::vec3& /*point*/) const
    {
        return m_color;
    }
}