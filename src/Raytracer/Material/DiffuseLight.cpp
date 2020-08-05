//
// Created by Platholl on 06/07/2020.
//

#include <utility>

#include "Raytracer/Material/DiffuseLight.hpp"

namespace rt
{
    DiffuseLight::DiffuseLight(std::shared_ptr<rt::Texture> texture):
        m_texture(std::move(texture))
    {
    }

    glm::vec3 DiffuseLight::Emitted(const Ray& /*rIn*/, const HitRecord& record) const
    {
        if(record.frontFace)
            return m_texture->Value(record.uv, record.point);
        else
            return glm::vec3{0, 0, 0};
    }
}