//
// Created by Platholl on 04/08/2020.
//

#ifndef RAYTRACER_ORTHONORMALBASE_HPP
#define RAYTRACER_ORTHONORMALBASE_HPP

#include <array>

#include <glm/glm.hpp>

namespace rt
{
    class OrthonormalBase
    {
    public:
        OrthonormalBase() = default;

        glm::vec3 operator[](int i) const { return m_axis[i]; }
        [[nodiscard]] glm::vec3 U() const { return m_axis[0]; }
        [[nodiscard]] glm::vec3 V() const { return m_axis[1]; }
        [[nodiscard]] glm::vec3 W() const { return m_axis[2]; }

        [[nodiscard]] glm::vec3 Local(float a, float b, float c) const
        {
            return a * U() + b * V() + c * W();
        }

        [[nodiscard]] glm::vec3 Local(const glm::vec3& a) const
        {
            return a[0] * U() + a[1] * V() + a[2] * W();
        }

        void BuildFromW(const glm::vec3& n);

    private:
        std::array<glm::vec3, 3> m_axis;
    };
}

#endif //RAYTRACER_ORTHONORMALBASE_HPP
