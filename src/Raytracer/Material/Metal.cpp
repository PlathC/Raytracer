//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Material/Metal.hpp"

namespace rt
{
    Metal::Metal(const Vec3f &albedo, const float fuzziness) :
        m_albedo(albedo),
        m_fuzziness(fuzziness)
    {}

    bool Metal::Scatter(const Ray &rIn, const HitRecord &record, Vec3f &attenuation, Ray &scattered) const
    {
        Vec3 reflected = Reflect(rIn.Direction().Normalize(), record.normal);
        scattered = Ray(record.point, reflected + m_fuzziness * RandomInUnitSphere<float>());
        attenuation = m_albedo;
        return (scattered.Direction().Dot(record.normal) > 0);
    }
}