//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Material/DiffuseLight.hpp"

namespace rt
{
    DiffuseLight::DiffuseLight(std::shared_ptr<rt::Texture> texture):
        m_texture(texture)
    {
    }

    bool DiffuseLight::Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& attenuation, Ray& scattered) const
    {
        return false;
    }

    glm::vec3 DiffuseLight::Emitted(const glm::vec2& uv, const glm::vec3& point) const
    {
        return m_texture->Value(uv, point);
    }
}