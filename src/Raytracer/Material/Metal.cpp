//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Material/Metal.hpp"
#include "Raytracer/Math/Math.hpp"

namespace rt
{
    Metal::Metal(const glm::vec3 &albedo, const float fuzziness) :
        m_albedo(albedo),
        m_fuzziness(fuzziness)
    {}

    bool Metal::Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& albedo, Ray& scattered, double& /*pdf*/) const
    {
        glm::vec3 reflected = Reflect(glm::normalize(rIn.Direction()), record.normal);
        scattered = Ray(record.point, reflected + m_fuzziness * RandomInUnitSphere());
        albedo = m_albedo;
        return glm::dot(scattered.Direction(), record.normal) > 0;
    }
}