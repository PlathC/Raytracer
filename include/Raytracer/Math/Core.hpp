//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_CORE_HPP
#define RAYTRACER_CORE_HPP

#include <array>
#include <limits>
#include <random>

#include <glm/glm.hpp>

namespace rt
{
    constexpr double Infinity = std::numeric_limits<double>::infinity();
    constexpr double Epsilon = std::numeric_limits<double>::epsilon();
    constexpr double Pi = 3.1415926535897932385;

    inline double DegreesToRadians(const double degrees)
    {
        return degrees * Pi / 180.;
    }

    template<class T>
    inline T Random(const T min, const T max)
    {
        if constexpr (std::is_integral_v<T>)
        {
            static std::uniform_int_distribution<T> distribution(min, max);
            static std::mt19937 generator;
            return distribution(generator);
        }
        else if (std::is_floating_point_v<T>)
        {
            static std::uniform_real_distribution<T> distribution(min, max);
            static std::mt19937 generator;
            return distribution(generator);
        }
    }

    template<class T>
    inline T Random()
    {
        return Random<T>(0, 1);
    }

    inline double Clamp(const double x, const double min, const double max)
    {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    inline double PerlinInterpolation(const std::array<std::array<std::array<glm::vec3, 2>, 2>, 2> c,
                                         const double u, const double v, const double w)
    {
        // Hermitian smoothing
        double uu = u * u * (3 - 2 * u);
        double vv = v * v * (3 - 2 * v);
        double ww = w * w * (3 - 2 * w);

        double accumulation = 0.;
        for(uint8_t i = 0; i < 2; i++)
        {
            for(uint8_t j = 0; j < 2; j++)
            {
                for(uint8_t k = 0; k < 2; k++)
                {
                    glm::vec3 weightV(u - i, v - j, w - k);
                    accumulation += (i * uu + (1 - i) * (1 - uu)) *
                                    (j * vv + (1 - j) * (1 - vv)) *
                                    (k * ww + (1 - k) * (1 - ww)) *
                                    glm::dot(c[i][j][k], weightV);
                }
            }
        }

        return accumulation;
    }

    inline double TrilinearInterpolation(const std::array<std::array<std::array<double, 2>, 2>, 2> c,
                                      const double u, const double v, const double w)
    {
        double accumulation = 0.;
        for(uint8_t i = 0; i < 2; i++)
        {
            for(uint8_t j = 0; j < 2; j++)
            {
                for(uint8_t k = 0; k < 2; k++)
                {
                    accumulation += (i * u + (1 - i) * (1 - u)) *
                                    (j * v + (1 - j) * (1 - v)) *
                                    (k * w + (1 - k) * (1 - w)) * c[i][j][k];
                }
            }
        }

        return accumulation;
    }

    inline double Schlick(double cosine, double refraction)
    {
        auto r0 = (1. - refraction) / (1.0 + refraction);
        r0 = r0*r0;
        return r0 + (1 - r0) * pow((1. - cosine), 5);
    }
}

#endif //RAYTRACER_CORE_HPP
