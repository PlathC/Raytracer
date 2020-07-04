//
// Created by Platholl on 28/06/2020.
//

#ifndef RAYTRACER_VEC_HPP
#define RAYTRACER_VEC_HPP

#include <cmath>
#include <iostream>

#include "Raytracer/Math/Core.hpp"

namespace rt
{
    template<class T>
    class Vec3
    {
    public:
        Vec3() : e{0, 0, 0} {}
        Vec3(T e0, T e1, T e2) : e{e0, e1, e2} {}

        T X() const { return e[0]; }
        T Y() const { return e[1]; }
        T Z() const { return e[2]; }

        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        T operator[](int i) const { return e[i]; }
        T& operator[](int i) { return e[i]; }

        Vec3<T>& operator+=(const Vec3<T>& v)
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3<T>& operator*=(const T t)
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        Vec3<T>& operator/=(const T t)
        {
            return *this *= 1/t;
        }

        double Length() const
        {
            return std::sqrt(SquaredLength());
        }

        T SquaredLength() const
        {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        T Dot(const Vec3<T>& v) const
        {
            return e[0] * v.X()
                   + e[1] * v.Y()
                   + e[2] * v.Z();
        }

        Vec3<T> Cross(const Vec3<T>& v) const
        {
            return Vec3(e[1] * v.Z() - e[2] * v.Z(),
                        e[2] * v.X() - e[0] * v.Z(),
                        e[0] * v.Y() - e[1] * v.X());
        }

        Vec3<T> Normalize() const
        {
            double length = Length();
            return Vec3<T>(static_cast<T>(e[0] / length),
                           static_cast<T>(e[1] / length),
                           static_cast<T>(e[2] / length));
        }

    private:
        T e[3];
    };

    template<class T>
    class Vec2
    {
    public:
        Vec2() : e{0, 0} {}
        Vec2(T e0, T e1) : e{e0, e1} {}

        T X() const { return e[0]; }
        T Y() const { return e[1]; }

        Vec2 operator-() const { return Vec2(-e[0], -e[1]); }
        T operator[](int i) const { return e[i]; }
        T& operator[](int i) { return e[i]; }

        Vec2<T>& operator+=(const Vec2<T>& v)
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            return *this;
        }

        Vec3<T>& operator*=(const T t)
        {
            e[0] *= t;
            e[1] *= t;
            return *this;
        }

        Vec3<T>& operator/=(const T t)
        {
            return *this *= 1/t;
        }

        double Length() const
        {
            return std::sqrt(SquaredLength());
        }

        T SquaredLength() const
        {
            return e[0]*e[0] + e[1]*e[1];
        }

        T Dot(const Vec2<T>& v) const
        {
            return e[0] * v.X()
                   + e[1] * v.Y();
        }

        Vec3<T> Cross(const Vec3<T>& v) const
        {
            return Vec2(e[0] * v.Y(), e[1] * v.X());
        }

        Vec3<T> Normalize() const
        {
            double length = Length();
            return Vec3<T>(static_cast<T>(e[0] / length),
                           static_cast<T>(e[1] / length));
        }

    private:
        T e[2];
    };

    using Vec3f = Vec3<float>;
    using Vec3d = Vec3<double>;

    template<class T>
    inline std::ostream& operator<<(std::ostream& out, const Vec3<T>& v)
    {
        return out << v.X() << ' ' << v.Y() << ' ' << v.Z();
    }

    template<class T>
    inline Vec3<T> operator+(const Vec3<T>& u, const Vec3<T>& v)
    {
        return Vec3(u.X() + v.X(), u.Y() + v.Y(), u.Z() + v.Z());
    }

    template<class T>
    inline Vec3<T> operator-(const Vec3<T>& u, const Vec3<T>& v)
    {
        return Vec3(u.X() - v.X(), u.Y() - v.Y(), u.Z() - v.Z());
    }

    template<class T>
    inline Vec3<T> operator*(const Vec3<T> &u, const Vec3<T> &v)
    {
        return Vec3(u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z());
    }

    template<class T>
    inline Vec3<T> operator*(T t, const Vec3<T>& v)
    {
        return Vec3(t * v.X(), t * v.Y(), t * v.Z());
    }

    template<class T>
    inline Vec3<T> operator*(const Vec3<T>& v, T t)
    {
        return t * v;
    }

    template<class T>
    inline Vec3<T> operator/(Vec3<T> v, T t)
    {
        return (1/t) * v;
    }

    template<class T>
    inline Vec3<T> VRandom()
    {
        return Vec3(Random<T>(), Random<T>(), Random<T>());
    }

    template<class T>
    inline Vec3<T> VRandom(const T min, const T max)
    {
        return Vec3<T>(Random<T>(min, max), Random<T>(min, max), Random<T>(min, max));
    }

    template<class T>
    inline Vec3<T> RandomInUnitSphere()
    {
        while(true)
        {
            Vec3<T> point = VRandom<T>(-1, 1);
            if(point.SquaredLength() >= 1) continue;
            return point;
        }
    }

    template<class T>
    inline Vec3<T> RandomUnitVector()
    {
        auto a = Random<T>(0, 2 * rt::Pi);
        auto z = Random<T>(-1, 1);
        auto r = std::sqrt(1 - z * z);

        return Vec3<T>(r * std::cos(a), r * std::sin(a), z);
    }

    template<class T>
    inline Vec3<T> RandomInHemisphere(const Vec3<T>& normal)
    {
        Vec3 inUnitSphere = RandomInUnitSphere();
        if (Dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
            return inUnitSphere;
        else
            return -inUnitSphere;
    }

    template<class T>
    inline Vec3<T> RandomInUnitDisk()
    {
        while (true)
        {
            auto p = Vec3<T>(Random<T>(-1, 1), Random<T>(-1, 1), 0);

            if (p.SquaredLength() >= 1) continue;
            return p;
        }
    }

    template<class T>
    inline Vec3<T> Reflect(const Vec3<T>& v, const Vec3<T>& n)
    {
        return v - 2 * v.Dot(n) * n;
    }

    template<class T>
    inline Vec3<T> Refract(const Vec3<T>& uv, const Vec3<T>& n, const T etaiOverEtat)
    {
        auto cosTheta = (-uv).Dot(n);
        Vec3 rOutParallel =  etaiOverEtat * (uv + cosTheta * n);
        Vec3 rOutPerp = -sqrt(1.f - rOutParallel.SquaredLength()) * n;
        return rOutParallel + rOutPerp;
    }

}

#endif //RAYTRACER_VEC_HPP
