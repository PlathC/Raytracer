//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_CORE_HPP
#define RAYTRACER_CORE_HPP

#include <limits>
#include <random>

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
        static std::uniform_real_distribution<T> distribution(min, max);
        static std::mt19937 generator;
        return distribution(generator);
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

    inline double Schlick(double cosine, double refraction) {
        auto r0 = (1. - refraction) / (1.0 + refraction);
        r0 = r0*r0;
        return r0 + (1 - r0) * pow((1. - cosine), 5);
    }
}

#endif //RAYTRACER_CORE_HPP
