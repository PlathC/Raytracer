//
// Created by Platholl on 06/07/2020.
//

#include "Raytracer/Math/Perlin.hpp"

namespace rt
{
    Perlin::Perlin(const uint32_t pointCount):
        m_pointCount(pointCount),
        m_randomVector(m_pointCount)
    {
        for(size_t i = 0; i < m_randomVector.size(); i++)
        {
            m_randomVector[i] = rt::VRandom(-1.f, 1.f);
        }

        GeneratePerlinPermutation(m_permutationX, m_pointCount);
        GeneratePerlinPermutation(m_permutationY, m_pointCount);
        GeneratePerlinPermutation(m_permutationZ, m_pointCount);
    }

    double Perlin::Noise(const glm::vec3& point) const
    {
        double u = point.x - std::floor(point.x);
        double v = point.y - std::floor(point.y);
        double w = point.z - std::floor(point.z);

        auto i = static_cast<int>(std::floor(point.x));
        auto j = static_cast<int>(std::floor(point.y));
        auto k = static_cast<int>(std::floor(point.z));

        std::array<std::array<std::array<glm::vec3, 2>, 2>, 2> values{};
        for(uint8_t di = 0; di < 2; di++)
        {
            for(uint8_t dj = 0; dj < 2; dj++)
            {
                for(uint8_t dk = 0; dk < 2; dk++)
                {
                    values[di][dj][dk] = m_randomVector[m_permutationX[(i + di) & (m_pointCount - 1)] ^
                                                        m_permutationY[(j + dj) & (m_pointCount - 1)] ^
                                                        m_permutationZ[(k + dk) & (m_pointCount - 1)]];
                }
            }
        }

        return PerlinInterpolation(values, u, v, w);
    }

    double Perlin::Turbulence(const glm::vec3& point, const uint8_t depth) const
    {
        double accumulation = 0.;
        glm::vec3 tempPoint = point;
        double weight = 1.;

        for(uint8_t i = 0; i < depth; i++)
        {
            accumulation += weight * Noise(tempPoint);
            weight *= 0.5;
            tempPoint *= 2;
        }

        return std::fabs(accumulation);
    }

    void Perlin::GeneratePerlinPermutation(std::vector<int>& p, const uint32_t pointCount)
    {
        p = std::vector<int>(pointCount);
        for(size_t i = 0; i < p.size(); i++)
        {
            p[i] = static_cast<int>(i);
        }

        Permute(p, pointCount);
    }

    void Perlin::Permute(std::vector<int>& p, int n)
    {
        for(size_t i = n - 1; i > 0; i--)
        {
            int target = rt::Random<int>(0, static_cast<int>(i));
            std::swap(p[i], p[target]);
        }
    }
}