//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Material/PerlinTexture.hpp"

namespace rt
{
    PerlinTexture::PerlinTexture(const float scale) :
        m_scale(scale)
    {
    }

    glm::vec3 PerlinTexture::Value(const glm::vec2& uv, const glm::vec3& point) const
    {
        return glm::vec3(1, 1, 1) * 0.5f * static_cast<float>(1.f + sin(m_scale * point.z + 10 * m_perlin.Turbulence(point)));
    }
}