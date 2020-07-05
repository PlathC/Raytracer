//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include <glm/glm.hpp>

#include "Raytracer/Math/Math.hpp"

namespace rt
{
    class Camera
    {
    public:
        Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUp, const float vFov,
                const float aspectRatio, const float aperture, const float focusDist, const double t0 = 0.,
                const double t1 = 0.);

        Ray GetRay(const float s, const float t) const;

    private:
        glm::vec3 m_origin;
        glm::vec3 m_lowerLeftCorner;
        glm::vec3 m_horizontal;
        glm::vec3 m_vertical;
        glm::vec3 u, v, w;
        float lensRadius;

        double m_time0;
        double m_time1;
    };
}

#endif //RAYTRACER_CAMERA_HPP
