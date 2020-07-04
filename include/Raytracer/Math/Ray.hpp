//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include "Raytracer/Math/Vec.hpp"

namespace rt
{
    class Ray
    {
    public:
        Ray() {}
        Ray(const Vec3f& origin, const Vec3f direction):
                m_origin(origin), m_direction(direction)
        {}

        Vec3f Origin() const { return m_origin; }
        Vec3f Direction() const { return m_direction; }

        Vec3f At(float t) const
        {
            return m_origin + t * m_direction;
        }

    private:
        Vec3f m_origin;
        Vec3f m_direction;
    };

}

#endif //RAYTRACER_RAY_HPP
