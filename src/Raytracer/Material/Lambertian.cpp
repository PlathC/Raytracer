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

    bool Lambertian::Scatter(const Ray& rIn, const HitRecord& record, glm::vec3& albedo, Ray& scattered, double& pdf) const
    {
        OrthonormalBase tempBase{};
        tempBase.BuildFromW(record.normal);
        auto scatterDirection = tempBase.Local(RandomCosineDirection<float>());
        scattered = Ray(record.point, glm::normalize(scatterDirection), rIn.Time());
        albedo = m_albedo->Value(record.uv, record.point);
        pdf = glm::dot(tempBase.W(), scatterDirection) / Pi;
        return true;
    }

    double Lambertian::ScatteringPdf(const Ray& /*rIn*/, const HitRecord& record, Ray& scattered) const
    {
        float cosine = glm::dot(record.normal, glm::normalize(scattered.Direction()));
        return cosine < 0 ? 0. : cosine / rt::Pi;
    }
}