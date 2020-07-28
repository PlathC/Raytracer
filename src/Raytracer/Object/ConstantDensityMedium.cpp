//
// Created by Platholl on 08/07/2020.
//

#include "Raytracer/Object/ConstantDensityMedium.hpp"

namespace rt
{
    ConstantDensityMedium::ConstantDensityMedium(std::shared_ptr<rt::IHittable> boundary,
            std::shared_ptr<rt::Texture> texture, double density):
            m_boundary(boundary),
            m_phaseFunction(std::make_shared<rt::Isotropic>(texture)),
            m_negativeInverseDensity(-1 / density)
    {
    }

    bool ConstantDensityMedium::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        // TODO: Handle non convex shapes
        // TODO: Add debug as general settings and with logger
        constexpr bool enableDebug = false;
        const bool outputDebug = enableDebug && rt::Random<double>() < 0.00001;

        HitRecord fRecord{}, sRecord{};

        // Compute the inside of the boundary
        if(!m_boundary->Hit(ray, -rt::Infinity<double>, rt::Infinity<double>, fRecord))
            return false;

        if(!m_boundary->Hit(ray, fRecord.t + 0.0001, rt::Infinity<double>, sRecord))
            return false;

        if(outputDebug) std::cerr << "\nt0=" << fRecord.t << ", t1=" << sRecord.t << "\n";

        if(fRecord.t < tMin) fRecord.t = static_cast<float>(tMin);
        if(sRecord.t > tMax) sRecord.t = static_cast<float>(tMax);

        if(fRecord.t >= sRecord.t) return false;

        if(fRecord.t < 0) fRecord.t = 0;

        const float rayLength = glm::length(ray.Direction());
        const float distanceInsideBoundary = (sRecord.t - fRecord.t) * rayLength;

        const float hitDistance = static_cast<float>(m_negativeInverseDensity) * std::log(Random<float>());

        if(hitDistance > distanceInsideBoundary)
            return false;

        record.t = fRecord.t + hitDistance / rayLength;
        record.point = ray.At(record.t);

        if(outputDebug)
        {
            std::cout << "Hit Distance = " << hitDistance << "\n"
                      << "record.t = " << record.t << "\n"
                      << "record.point = " << record.point.x << "/" << record.point.y <<  "/"
                      << record.point.z << "\n";
        }
        record.normal = glm::vec3(1, 0, 0); // Arbitrary
        record.frontFace = true; // idem
        record.material = m_phaseFunction.get();

        return true;
    }

    bool ConstantDensityMedium::BoundingBox(const double t0, const double t1, AABB& box) const
    {
        return m_boundary->BoundingBox(t0, t1, box);
    }
}
