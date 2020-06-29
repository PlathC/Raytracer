//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include "Raytracer/Math/Vec3.hpp"

namespace rt
{
    class Ray
    {
    public:
        Ray() {}
        Ray(const Point3& origin, const Vec3 direction):
                m_origin(origin), m_direction(direction)
        {}

        Point3 Origin() const { return m_origin; }
        Vec3 Direction() const { return m_direction; }

        Point3 At(double t) const
        {
            return m_origin + t * m_direction;
        }

    private:
        Point3 m_origin;
        Vec3 m_direction;
    };

}

#endif //RAYTRACER_RAY_HPP
