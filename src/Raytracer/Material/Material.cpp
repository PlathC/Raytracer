//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    glm::vec3 Material::Emitted(const glm::vec2& /*uv*/, const glm::vec3& /*p*/) const
    {
        return glm::vec3(0, 0, 0);
    }
}
