//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Utils/Camera.hpp"

namespace rt
{
    Camera::Camera(const Vec3f& lookFrom, const Vec3f& lookAt, const Vec3f& vUp, const float vfov,
                   const float aspectRatio, const float aperture, const float focusDist):
        m_origin(lookFrom)
    {
        const float theta = DegreesToRadians(vfov);
        const float h = std::tan(theta / 2.);
        const float viewportHeight = 2.0 * h;
        const float viewportWidth = aspectRatio * viewportHeight;

        w = (lookFrom - lookAt).Normalize();
        u = vUp.Cross(w).Normalize();
        v = w.Cross(u);

        m_horizontal = focusDist * viewportWidth * u;
        m_vertical = focusDist * viewportHeight * v;
        m_lowerLeftCorner = m_origin - m_horizontal / 2.f - m_vertical / 2.f - focusDist * w;

        lensRadius = aperture / 2.f;
    }

    Ray Camera::GetRay(const float s, const float t) const
    {
        Vec3f rd = lensRadius * RandomInUnitDisk<float>();
        Vec3f offset = u * rd.X() + v * rd.Y();

        return rt::Ray(m_origin + offset,
                m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset
        );
    }
}