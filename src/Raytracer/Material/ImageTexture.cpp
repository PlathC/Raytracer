//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Material/ImageTexture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace rt
{
    ImageTexture::ImageTexture(const std::string& fileName):
        m_width{},
        m_height{},
        m_data{}
    {
        int width{}, height{}, channels{};
        uint8_t* imgData = stbi_load(fileName.c_str(), &width, &height, &channels, ChannelNumber);
        if(!imgData)
        {
            throw std::runtime_error("Can't find the following file : " + fileName);
        }

        m_width = width;
        m_height = height;

        m_data = std::vector(imgData, imgData + (width * height * channels));
    }

    glm::vec3 ImageTexture::Value(const glm::vec2& uv, const glm::vec3& /*points*/) const
    {
        if(m_data.empty())
        {
            // Default debug color
            // TODO: Set this as expressive const
            return glm::vec3(0, 1, 1);
        }

        double u{uv.x}, v{uv.y};

        // Take care that u and v are in [0, 1]
        u = rt::Clamp(u, 0., 1.);
        v = 1. - rt::Clamp(v, 0., 1.); // Flip v to image coordinates

        auto i = static_cast<uint32_t>(u * m_width);
        auto j = static_cast<uint32_t>(v * m_height);

        if(i >= m_width)  i = m_width - 1;
        if(j >= m_height) j = m_height - 1;

        constexpr float scale = 1.f / 255.f;
        const uint32_t pixelIndex = j * (ChannelNumber * m_width) + i * ChannelNumber;
        glm::vec3 pixel = glm::vec3{m_data[pixelIndex],
                                    m_data[pixelIndex + 1],
                                    m_data[pixelIndex + 2]};

        return scale * pixel;
    }
}