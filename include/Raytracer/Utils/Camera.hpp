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
        Camera(const Vec3f& lookFrom, const Vec3f& lookAt, const Vec3f& vUp, const float vfov,
                const float aspectRatio, const float aperture, const float focusDist);

        Ray GetRay(const float s, const float t) const;

    private:
        Vec3f m_origin;
        Vec3f m_lowerLeftCorner;
        Vec3f m_horizontal;
        Vec3f m_vertical;
        Vec3f u, v, w;
        float lensRadius;

    };
}

#endif //RAYTRACER_CAMERA_HPP
