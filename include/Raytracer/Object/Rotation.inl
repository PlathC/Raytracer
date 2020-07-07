//
// Created by Platholl on 07/07/2020.
//

#include "Raytracer/Object/Rotation.hpp"

namespace rt
{
    template<uint8_t axis>
    Rotation<axis>::Rotation(std::unique_ptr<Hittable> object, float angle):
        m_object(std::move(object))
    {
        glm::vec3 rotationAxis = glm::vec3{0, 0, 0};
        rotationAxis[axis] = 1;
        m_rotationMatrix = glm::rotate(angle, rotationAxis);
        m_haveBoundingBox = m_object->BoundingBox(0, 1, m_boundingBox);

        if(m_haveBoundingBox)
        {
            glm::vec4 nMin = m_rotationMatrix * glm::vec4(m_boundingBox.Minimum(), 0);
            glm::vec4 nMax = m_rotationMatrix * glm::vec4(m_boundingBox.Maximum(), 0);
            m_boundingBox = AABB{
                    glm::vec3(nMin.x, nMin.y, nMin.z),
                    glm::vec3(nMax.x, nMax.y, nMax.z),
            };
        }
    }

    template<uint8_t axis>
    bool Rotation<axis>::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        glm::vec4 nOrigin    = m_rotationMatrix * glm::vec4(ray.Origin(), 0);
        glm::vec4 nDirection = m_rotationMatrix * glm::vec4(ray.Direction(), 1);
        Ray rotatedRay = Ray{
                glm::vec3(nOrigin.x, nOrigin.y, nOrigin.z),
                glm::vec3(nDirection.x, nDirection.y, nDirection.z),
                ray.Time()
        };

        if(!m_object->Hit(rotatedRay, tMin, tMax, record))
            return false;

        glm::vec4 nPoint  = m_rotationMatrix * glm::vec4(record.point, 0);
        glm::vec4 nNormal = m_rotationMatrix * glm::vec4(record.point, 1);

        record.point  = glm::vec3(nPoint.x, nPoint.y, nPoint.z);
        record.normal = glm::vec3(nNormal.x, nNormal.y, nNormal.z);
        record.SetFaceNormal(rotatedRay, record.normal);

        return true;
    }

    template<uint8_t axis>
    bool Rotation<axis>::BoundingBox(const double t0, const double t1, AABB& box) const
    {
        box = m_boundingBox;
        return m_haveBoundingBox;
    }
}
