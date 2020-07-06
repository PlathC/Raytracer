//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_TEXTURE_HPP
#define RAYTRACER_TEXTURE_HPP

#include "Raytracer/Math/Math.hpp"

namespace rt
{
    class Texture
    {
    public:
        virtual glm::vec3 Value(const glm::vec2& uv, const glm::vec3& point) const = 0;

        virtual ~Texture() = default;
    };
}


#endif //RAYTRACER_TEXTURE_HPP
