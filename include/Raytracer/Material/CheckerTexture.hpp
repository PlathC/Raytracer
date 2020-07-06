//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_CHECKERTEXTURE_HPP
#define RAYTRACER_CHECKERTEXTURE_HPP

#include "Raytracer/Material/Texture.hpp"

namespace rt
{
    class CheckerTexture : public Texture
    {
    public:
        CheckerTexture() = default;
        CheckerTexture(std::unique_ptr<Texture> t0, std::unique_ptr<Texture> t1, const uint32_t size = 10);

        virtual glm::vec3 Value(const glm::vec2& uv, const glm::vec3& point) const override;

        virtual ~CheckerTexture() = default;

    private:
        std::unique_ptr<Texture> m_oddTexture;
        std::unique_ptr<Texture> m_evenTexture;
        uint32_t m_size;
    };
}

#endif //RAYTRACER_CHECKERTEXTURE_HPP
