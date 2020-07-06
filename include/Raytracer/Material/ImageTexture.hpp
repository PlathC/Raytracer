//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_IMAGETEXTURE_HPP
#define RAYTRACER_IMAGETEXTURE_HPP

#include "Raytracer/Material/Texture.hpp"

namespace rt
{
    class ImageTexture : public Texture
    {
    public:
        ImageTexture() = default;
        ImageTexture(const std::string& fileName);

        virtual glm::vec3 Value(const glm::vec2& uv, const glm::vec3& points) const override;

    private:
        //TODO: Handle alpha channel
        constexpr static uint8_t ChannelNumber = 3;
        uint32_t m_width;
        uint32_t m_height;
        std::vector<uint8_t> m_data;
    };
}

#endif //RAYTRACER_IMAGETEXTURE_HPP
