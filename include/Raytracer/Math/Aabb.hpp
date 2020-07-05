//
// Created by Platholl on 05/07/2020.
//

#ifndef RAYTRACER_AABB_HPP
#define RAYTRACER_AABB_HPP

#include <cmath>
#include <utility>

#include <glm/vec3.hpp>

#include "Raytracer/Math/Ray.hpp"

namespace rt
{
    class AABB
    {
    public:
        AABB() = default;
        AABB(const glm::vec3& minimum, const glm::vec3& maximum);

        // Compute surrounding box
        AABB(const AABB& fBox, const AABB& sBox);

        glm::vec3 Minimum() const;
        glm::vec3 Maximum() const;

        bool Hit(const rt::Ray& ray, double tMin, double tMax) const;
    private:
        glm::vec3 m_minimum;
        glm::vec3 m_maximum;
    };
}

#endif //RAYTRACER_AABB_HPP
