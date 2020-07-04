//
// Created by Platholl on 28/06/2020.
//

#include "Raytracer/Utils/Camera.hpp"

namespace rt
{
    Camera::Camera(const Point3& lookFrom, const Point3& lookAt, const Vec3& vUp, const double vfov,
                   const double aspectRatio, const double aperture, const double focusDist):
        m_origin(lookFrom)
    {
        const double theta = DegreesToRadians(vfov);
        const double h = std::tan(theta / 2.);
        const double viewportHeight = 2.0 * h;
        const double viewportWidth = aspectRatio * viewportHeight;

        w = rt::UnitVector(lookFrom - lookAt);
        u = rt::UnitVector(rt::Cross(vUp, w));
        v = rt::Cross(w, u);

        m_horizontal = focusDist * viewportWidth * u;
        m_vertical = focusDist * viewportHeight * v;
        m_lowerLeftCorner = m_origin - m_horizontal / 2. - m_vertical / 2. - focusDist * w;

        lensRadius = aperture / 2.;
    }

    Ray Camera::GetRay(const double s, const double t) const
    {
        Vec3 rd = lensRadius * RandomInUnitDisk();
        Vec3 offset = u * rd.X() + v * rd.Y();

        return rt::Ray(m_origin + offset,
                m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset
        );
    }
}