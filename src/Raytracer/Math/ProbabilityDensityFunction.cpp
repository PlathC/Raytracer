//
// Created by Platholl on 05/08/2020.
//

#include "Raytracer/Math/ProbabilityDensityFunction.hpp"
#include "Raytracer/Object/IHittable.hpp"

namespace rt
{
    CosineProbabilityDensityFunction::CosineProbabilityDensityFunction(const glm::vec3& w)
    {
        m_base.BuildFromW(w);
    }

    double CosineProbabilityDensityFunction::Value(const glm::vec3& direction) const
    {
        float cosine = glm::dot(glm::normalize(direction), m_base.W());
        return (cosine <= 0.) ? 0 : cosine / rt::Pi;
    }

    glm::vec3 CosineProbabilityDensityFunction::Generate() const
    {
        return m_base.Local(rt::RandomCosineDirection<float>());
    }

    HittableProbabilityDensityFunction::HittableProbabilityDensityFunction(std::shared_ptr<rt::IHittable> object,
                                                                           const glm::vec3& origin):
        m_object(object),
        m_origin(origin)
    {
    }

    double HittableProbabilityDensityFunction::Value(const glm::vec3& direction) const
    {
        return m_object->PdfValue(m_origin, direction);
    }

    glm::vec3 HittableProbabilityDensityFunction::Generate() const
    {
        return m_object->Random(m_origin);
    }

    MixtureProbabilityDensityFunction::MixtureProbabilityDensityFunction(
            std::shared_ptr<ProbabilityDensityFunction> firstFunction,
            std::shared_ptr<ProbabilityDensityFunction> secondFunction):
        m_functions({std::move(firstFunction), std::move(secondFunction)})
    {
    }

    double MixtureProbabilityDensityFunction::Value(const glm::vec3& direction) const
    {
        return 0.5 * m_functions[0]->Value(direction) + 0.5 * m_functions[1]->Value(direction);
    }

    glm::vec3 MixtureProbabilityDensityFunction::Generate() const
    {
        if(rt::Random<double>() < 0.5)
            return m_functions[0]->Generate();
        else
            return m_functions[1]->Generate();
    }
}