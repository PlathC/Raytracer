//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Material/Metal.hpp"

namespace rt
{
    Metal::Metal(const Color &albedo, const double fuzziness) :
        m_albedo(albedo),
        m_fuzziness(fuzziness)
    {}

    bool Metal::Scatter(const Ray &rIn, const HitRecord &record, Color &attenuation, Ray &scattered) const
    {
        Vec3 reflected = Reflect(UnitVector(rIn.Direction()), record.normal);
        scattered = Ray(record.point, reflected + m_fuzziness * RandomInUnitSphere());
        attenuation = m_albedo;
        return (Dot(scattered.Direction(), record.normal) > 0);
    }
}