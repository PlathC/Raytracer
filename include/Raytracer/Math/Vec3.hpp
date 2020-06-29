//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_VEC3_HPP
#define RAYTRACER_VEC3_HPP

#include <cmath>
#include <iostream>

#include "Raytracer/Math/Core.hpp"

namespace rt
{
    class Vec3
    {
    public:
        Vec3() : e{0, 0, 0} {}
        Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double X() const { return e[0]; }
        double Y() const { return e[1]; }
        double Z() const { return e[2]; }

        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vec3& operator+=(const Vec3& v)
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator*=(const double t)
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3& operator/=(const double t)
        {
            return *this *= 1/t;
        }

        double Length() const
        {
            return std::sqrt(SquaredLength());
        }

        double SquaredLength() const
        {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

    private:
        double e[3];
    };

    using Point3 = Vec3;
    using Color  = Vec3;

    inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
    {
        return out << v.X() << ' ' << v.Y() << ' ' << v.Z();
    }

    inline Vec3 operator+(const Vec3& u, const Vec3& v)
    {
        return Vec3(u.X() + v.X(), u.Y() + v.Y(), u.Z() + v.Z());
    }

    inline Vec3 operator-(const Vec3& u, const Vec3& v)
    {
        return Vec3(u.X() - v.X(), u.Y() - v.Y(), u.Z() - v.Z());
    }

    inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
    {
        return Vec3(u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z());
    }

    inline Vec3 operator*(double t, const Vec3& v)
    {
        return Vec3(t * v.X(), t * v.Y(), t * v.Z());
    }

    inline Vec3 operator*(const Vec3& v, double t)
    {
        return t * v;
    }

    inline Vec3 operator/(Vec3 v, double t)
    {
        return (1/t) * v;
    }

    inline double Dot(const Vec3& u, const Vec3& v)
    {
        return u.X() * v.X()
               + u.Y() * v.Y()
               + u.Z() * v.Z();
    }

    inline Vec3 Cross(const Vec3& u, const Vec3& v)
    {
        return Vec3(u.Y() * v.Z() - u.Z() * v.Z(),
                    u.Z() * v.X() - u.X() * v.Z(),
                    u.X() * v.Y() - u.Y() * v.X());
    }

    inline Vec3 UnitVector(Vec3 v)
    {
        return v / v.Length();
    }

    inline Vec3 Random()
    {
        return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    inline Vec3 Random(const double min, const double max)
    {
        return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

    inline Vec3 RandomInUnitSphere()
    {
        while(true)
        {
            Vec3 point = Random(-1., 1.);
            if(point.SquaredLength() >= 1) continue;
            return point;
        }
    }

    inline Vec3 RandomUnitVector()
    {
        auto a = RandomDouble(0, 2*Pi);
        auto z = RandomDouble(-1, 1);
        auto r = std::sqrt(1 - z * z);

        return Vec3(r * std::cos(a), r * std::sin(a), z);
    }

    inline Vec3 RandomInHemisphere(const Vec3& normal)
    {
        Vec3 inUnitSphere = RandomInUnitSphere();
        if (Dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
            return inUnitSphere;
        else
            return -inUnitSphere;
    }

    inline Vec3 Reflect(const Vec3& v, const Vec3& n)
    {
        return v - 2 * Dot(v, n) * n;
    }

    inline Vec3 refract(const Vec3& uv, const Vec3& n, const double etaiOverEtat) {
        auto cosTheta = Dot(-uv, n);
        Vec3 rOutParallel =  etaiOverEtat * (uv + cosTheta * n);
        Vec3 rOutPerp = -sqrt(1.0 - rOutParallel.SquaredLength()) * n;
        return rOutParallel + rOutPerp;
    }

    inline Vec3 RandomInUnitDisk()
    {
        while (true)
        {
            auto p = Vec3(RandomDouble(-1,1), RandomDouble(-1,1), 0);

            if (p.SquaredLength() >= 1) continue;
            return p;
        }
    }

}

#endif //RAYTRACER_VEC3_HPP
