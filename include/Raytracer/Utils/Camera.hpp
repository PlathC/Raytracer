//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "Raytracer/Math/Math.hpp"

namespace rt
{
    class Camera
    {
    public:
        Camera(const Point3& lookFrom, const Point3& lookAt, const Vec3& vUp, const double vfov,
                const double aspectRatio, const double aperture, const double focusDist);

        Ray GetRay(const double s, const double t) const;

    private:
        Point3 m_origin;
        Point3 m_lowerLeftCorner;
        Vec3 m_horizontal;
        Vec3 m_vertical;
        Vec3 u, v, w;
        double lensRadius;

    };
}

#endif //RAYTRACER_CAMERA_HPP
