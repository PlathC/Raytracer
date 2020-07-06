//
// Created by Platholl on 06/07/2020.
//

#ifndef RAYTRACER_PERLIN_HPP
#define RAYTRACER_PERLIN_HPP

#include <vector>

#include <glm/vec3.hpp>

#include "Raytracer/Math/Core.hpp"
#include "Raytracer/Math/Vec.hpp"

namespace rt
{
    class Perlin
    {
    public:
        Perlin(const uint32_t pointCount = 256);

        double Noise(const glm::vec3& point) const;
        double Turbulence(const glm::vec3& point, const uint8_t depth = 7) const;

    private:
        const uint32_t m_pointCount;
        std::vector<glm::vec3> m_randomVector;
        std::vector<int> m_permutationX;
        std::vector<int> m_permutationY;
        std::vector<int> m_permutationZ;

        static void GeneratePerlinPermutation(std::vector<int>& p, const uint32_t pointCount);
        static void Permute(std::vector<int>& p, int n);
    };
}

#endif //RAYTRACER_PERLIN_HPP
