//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_VEC_HPP
#define RAYTRACER_VEC_HPP

#include <cmath>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

#include "Raytracer/Math/Core.hpp"

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

    template<class T>
    inline glm::vec3 RandomInUnitSphere()
    {
        while(true)
        {
            glm::vec3 point = VRandom<T>(-1, 1);
            if(glm::length2(point) >= 1) continue;
            return point;
        }
    }

    template<class T>
    inline glm::vec3 RandomUnitVector()
    {
        auto a = Random<T>(0, 2 * rt::Pi);
        auto z = Random<T>(-1, 1);
        auto r = std::sqrt(1 - z * z);

        return glm::vec3(r * std::cos(a), r * std::sin(a), z);
    }

    template<class T>
    inline glm::vec3 RandomInHemisphere(const glm::vec3& normal)
    {
        glm::vec3 inUnitSphere = RandomInUnitSphere();
        if (Dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
            return inUnitSphere;
        else
            return -inUnitSphere;
    }

    template<class T>
    inline glm::vec3 RandomInUnitDisk()
    {
        while (true)
        {
            auto p = glm::vec3(Random<T>(-1, 1), Random<T>(-1, 1), 0);

            if (glm::length2(p) >= 1) continue;
            return p;
        }
    }

    inline glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n)
    {
        return v - 2 * glm::dot(v, n) * n;
    }

    inline glm::vec3 Refract(const glm::vec3& uv, const glm::vec3& n, const float etaiOverEtat)
    {
        auto cosTheta = glm::dot(-uv, n);
        glm::vec3 rOutParallel =  etaiOverEtat * (uv + cosTheta * n);
        glm::vec3 rOutPerp = -sqrt(1.f - glm::length2(rOutParallel)) * n;
        return rOutParallel + rOutPerp;
    }

}

#endif //RAYTRACER_VEC_HPP
