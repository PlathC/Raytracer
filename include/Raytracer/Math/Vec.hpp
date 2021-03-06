//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_VEC_HPP
#define RAYTRACER_VEC_HPP

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "Raytracer/Math/Math.hpp"

namespace rt
{

    template<class T>
    inline glm::vec3 VRandom()
    {
        return glm::vec3(Random<T>(), Random<T>(), Random<T>());
    }

    template<class T>
    inline glm::vec3 VRandom(const T min, const T max)
    {
        return glm::vec3(Random<T>(min, max), Random<T>(min, max), Random<T>(min, max));
    }

    inline glm::vec3 RandomInUnitSphere()
    {
        while(true)
        {
            glm::vec3 point = VRandom<float>(-1, 1);
            if(glm::length2(point) >= 1) continue;
            return point;
        }
    }

    inline glm::vec3 RandomUnitVector()
    {
        //TODO: Fix this generation which is clearly not correct.
        double a = Random<double>(0, 2 * rt::Pi);
        double z = Random<double>(-1, 1);
        double r = std::sqrt(1 - z * z);

        return glm::vec3(r * std::cos(a), r * std::sin(a), z);
    }

    inline glm::vec3 RandomInHemisphere(const glm::vec3& normal)
    {
        glm::vec3 inUnitSphere = RandomInUnitSphere();
        if (glm::dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
            return inUnitSphere;
        else
            return -inUnitSphere;
    }

    template<class T>
    inline glm::vec3 RandomInUnitDisk()
    {
        while (true)
        {
            auto p = glm::vec3(Random<T>(-1., 1.), Random<T>(-1., 1.), 0.);

            if (glm::length2(p) >= 1) continue;
            return p;
        }
    }

    template<class T>
    inline glm::vec3 RandomCosineDirection()
    {
        auto randNumb1 = Random<T>();
        auto randNumb2 = Random<T>();
        double z = std::sqrt(1 - randNumb2);

        double phi = 2. * rt::Pi * randNumb1;
        double x = std::cos(phi) * std::sqrt(randNumb2);
        double y = std::sin(phi) * std::sqrt(randNumb2);

        return {x, y, z};
    }

    inline glm::vec3 RandomToSphere(double radius, double distanceSquared)
    {
        auto randomNum1 = rt::Random<float>();
        auto randomNum2 = rt::Random<float>();
        float z = 1 + randomNum2 * (std::sqrt(1 - radius * radius / distanceSquared) - 1);

        float phi = 2.f * static_cast<float>(rt::Pi) * randomNum1;
        float x = std::cos(phi) * std::sqrt(1 - z * z);
        float y = std::sin(phi) * std::sqrt(1 - z * z);

        return {x, y, z};
    }

    inline glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n)
    {
        return v - 2.f * glm::dot(v, n) * n;
    }

    inline glm::vec3 Refract(const glm::vec3& uv, const glm::vec3& n, const float etaiOverEtat)
    {
        float cosTheta = std::fmin(glm::dot(-uv, n), 1.f);
        glm::vec3 rOutParallel =  etaiOverEtat * (uv + cosTheta * n);
        glm::vec3 rOutPerp = -std::sqrt(1.f - glm::length2(rOutParallel)) * n;
        return rOutParallel + rOutPerp;
    }

}

#endif //RAYTRACER_VEC_HPP
