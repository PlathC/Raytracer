//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    bool Material::Scatter(const Ray& /*rIn*/, const HitRecord& /*record*/, ScatterRecord& /*sRecord*/) const
    {
        return false;
    }

    double Material::ScatteringPdf(const Ray& /*rIn*/, const HitRecord& /*record*/, Ray& /*scattered*/) const
    {
        return 0;
    }

    glm::vec3 Material::Emitted(const Ray& /*rIn*/, const HitRecord& /*record*/) const
    {
        return glm::vec3(0, 0, 0);
    }
}
