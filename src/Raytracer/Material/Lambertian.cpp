//
// Created by Platholl on 28/06/2020.
//

#include <utility>

#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Math/OrthonormalBase.hpp"

namespace rt
{
    Lambertian::Lambertian(std::shared_ptr<Texture> albedo) :
        m_albedo(std::move(albedo))
    {}

    bool Lambertian::Scatter(const Ray& /*rIn*/, const HitRecord& record, ScatterRecord& sRecord) const
    {
        sRecord.isSpecular = false;
        sRecord.albedo = m_albedo->Value(record.uv, record.point);
        sRecord.pdf = std::make_shared<CosineProbabilityDensityFunction>(record.normal);

        return true;
    }

    double Lambertian::ScatteringPdf(const Ray& /*rIn*/, const HitRecord& record, Ray& scattered) const
    {
        float cosine = glm::dot(record.normal, glm::normalize(scattered.Direction()));
        return cosine < 0 ? 0. : cosine / rt::Pi;
    }
}