//
// Created by Platholl on 05/08/2020.
//

#ifndef RAYTRACER_PROBABILITYDENSITYFUNCTION_HPP
#define RAYTRACER_PROBABILITYDENSITYFUNCTION_HPP

#include <array>

#include <glm/glm.hpp>

#include "Raytracer/Math/Math.hpp"
#include "Raytracer/Math/OrthonormalBase.hpp"

namespace rt
{
    class ProbabilityDensityFunction
    {
    public:
        [[nodiscard]] virtual double Value(const glm::vec3& direction) const = 0;
        [[nodiscard]] virtual glm::vec3 Generate() const = 0;

        virtual ~ProbabilityDensityFunction() = default;
    };

    class CosineProbabilityDensityFunction : public ProbabilityDensityFunction
    {
    public:
        explicit CosineProbabilityDensityFunction(const glm::vec3& w);

        [[nodiscard]] double Value(const glm::vec3& direction) const override;
        [[nodiscard]] glm::vec3 Generate() const override;
    private:
        OrthonormalBase m_base;
    };

    class IHittable;

    class HittableProbabilityDensityFunction : public ProbabilityDensityFunction
    {
    public:
        HittableProbabilityDensityFunction(std::shared_ptr<rt::IHittable> object, const glm::vec3& origin);

        [[nodiscard]] double Value(const glm::vec3& direction) const override;
        [[nodiscard]] glm::vec3 Generate() const override;
    private:
        std::shared_ptr<rt::IHittable> m_object;
        glm::vec3 m_origin;
    };

    class MixtureProbabilityDensityFunction : ProbabilityDensityFunction
    {
    public:
        MixtureProbabilityDensityFunction(std::shared_ptr<ProbabilityDensityFunction> firstFunction,
                                          std::shared_ptr<ProbabilityDensityFunction> secondFunction);

        [[nodiscard]] double Value(const glm::vec3& direction) const override;
        [[nodiscard]] glm::vec3 Generate() const override;

    private:
        std::array<std::shared_ptr<ProbabilityDensityFunction>, 2> m_functions;
    };
}


#endif //RAYTRACER_PROBABILITYDENSITYFUNCTION_HPP
