//
// Created by Platholl on 04/08/2020.
//

#include "Raytracer/Math/OrthonormalBase.hpp"

namespace rt
{
    void OrthonormalBase::BuildFromW(const glm::vec3& n)
    {
        m_axis[2] = glm::normalize(n);
        glm::vec3 a = (std::fabs(W().x) > 0.9) ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0);
        m_axis[1] = glm::normalize(glm::cross(W(), a));
        m_axis[0] = glm::cross(W(), V());
    }
}