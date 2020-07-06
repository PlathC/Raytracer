//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Material/CheckerTexture.hpp"

namespace rt
{
    CheckerTexture::CheckerTexture(std::unique_ptr<Texture> t0, std::unique_ptr<Texture> t1, const uint32_t size):
        m_oddTexture(std::move(t0)),
        m_evenTexture(std::move(t1)),
        m_size(size)
    {
    }

    glm::vec3 CheckerTexture::Value(const glm::vec2& uv, const glm::vec3& point) const
    {
        float sineWave = std::sin(m_size * point.x) * std::sin(m_size * point.y) * std::sin(m_size * point.z);
        if(sineWave < 0)
        {
            return m_oddTexture->Value(uv, point);
        }
        else
        {
            return m_evenTexture->Value(uv, point);
        }
    }
}