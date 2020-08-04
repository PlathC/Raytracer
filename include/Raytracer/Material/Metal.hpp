//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_METAL_HPP
#define RAYTRACER_METAL_HPP

#include "Raytracer/Material/Material.hpp"

namespace rt
{
    class Metal : public Material
    {
    public:
        Metal(const glm::vec3& albedo, const float fuzziness);

        bool Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& albedo, Ray& scattered, double& pdf) const override;

    private:
        glm::vec3 m_albedo;
        float m_fuzziness;
    };
}

#endif //RAYTRACER_METAL_HPP
