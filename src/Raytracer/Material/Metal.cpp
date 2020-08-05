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

    bool Metal::Scatter(const Ray& rIn, const HitRecord& record, ScatterRecord& scatterRecord) const
    {
        glm::vec3 reflected = Reflect(glm::normalize(rIn.Direction()), record.normal);

        scatterRecord.specularRay = Ray(record.point, reflected + m_fuzziness * RandomInUnitSphere());
        scatterRecord.albedo = m_albedo;
        scatterRecord.isSpecular = true;
        scatterRecord.pdf = nullptr;

        return true;
    }
}