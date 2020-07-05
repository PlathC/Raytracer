//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include <glm/vec3.hpp>

namespace rt
{
    class Ray
    {
    public:
        Ray() {}
        Ray(const glm::vec3& origin, const glm::vec3& direction, const double time = 0.0):
                m_origin(origin), m_direction(direction), m_time(time)
        {}

        glm::vec3 Origin() const { return m_origin; }
        glm::vec3 Direction() const { return m_direction; }
        double Time() const { return m_time; }

        glm::vec3 At(float t) const
        {
            return m_origin + t * m_direction;
        }

    private:
        glm::vec3 m_origin;
        glm::vec3 m_direction;
        double m_time;
    };

}

#endif //RAYTRACER_RAY_HPP
