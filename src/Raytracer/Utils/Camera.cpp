//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Utils/Camera.hpp"

namespace rt
{
    Camera::Camera(const glm::vec3& lookFrom, const glm::vec3& lookAt, const glm::vec3& vUp, const float vFov,
                   const float aspectRatio, const float aperture, const float focusDist):
        m_origin(lookFrom)
    {
        const float theta = DegreesToRadians(vFov);
        const float h = std::tan(theta / 2.);
        const float viewportHeight = 2.0 * h;
        const float viewportWidth = aspectRatio * viewportHeight;

        w = glm::normalize(lookFrom - lookAt);
        u = glm::normalize(glm::cross(vUp, w));
        v = glm::cross(w, u);

        m_horizontal = focusDist * viewportWidth * u;
        m_vertical = focusDist * viewportHeight * v;
        m_lowerLeftCorner = m_origin - m_horizontal / 2.f - m_vertical / 2.f - focusDist * w;

        lensRadius = aperture / 2.f;
    }

    Ray Camera::GetRay(const float s, const float t) const
    {
        glm::vec3 rd = lensRadius * RandomInUnitDisk<float>();
        glm::vec3 offset = u * rd.x + v * rd.y + w * rd.z;
        glm::vec3 direction = (m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset);
        direction = glm::normalize(direction);
        return rt::Ray(m_origin + offset, direction);
    }
}