//
// Created by Platholl on 07/07/2020.
//

#include "Raytracer/Object/Rotation.hpp"

namespace rt
{
    template<uint8_t axis>
    Rotation<axis>::Rotation(std::shared_ptr<IHittable> object, float angle):
        m_object(object)
    {
        glm::vec3 rotationAxis = glm::vec3{0, 0, 0};
        rotationAxis[axis] = 1;
        m_rotationMatrix = glm::rotate(static_cast<float>(rt::DegreesToRadians(angle)), rotationAxis);
        m_haveBoundingBox = m_object->BoundingBox(0, 1, m_boundingBox);

        if(m_haveBoundingBox)
        {
            glm::vec3 min = m_boundingBox.Minimum();
            glm::vec3 max = m_boundingBox.Maximum();

            for(uint8_t i = 0; i < 2; i++)
            {
                for(uint8_t j = 0; j < 2; j++)
                {
                    for(uint8_t k = 0; k < 2; k++)
                    {
                        glm::vec3 newVec = {
                                i * m_boundingBox.Maximum().x + (1 - i) * m_boundingBox.Minimum().x,
                                j * m_boundingBox.Maximum().y + (1 - j) * m_boundingBox.Minimum().y,
                                k * m_boundingBox.Maximum().z + (1 - k) * m_boundingBox.Minimum().z,
                        };

                        newVec = m_rotationMatrix * glm::vec4(newVec, 0);

                        for(uint8_t c = 0; c < 2; c++)
                        {
                            min[c] = std::fmin(min[c], newVec[c]);
                            max[c] = std::fmax(max[c], newVec[c]);
                        }
                    }
                }
            }
            m_boundingBox = AABB{
                    min,
                    max,
            };
        }
    }

    template<uint8_t axis>
    bool Rotation<axis>::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        glm::vec4 nOrigin    = glm::transpose(m_rotationMatrix) * glm::vec4(ray.Origin(), 0);
        glm::vec4 nDirection = glm::transpose(m_rotationMatrix) * glm::vec4(ray.Direction(), 1);
        Ray rotatedRay = Ray{
                glm::vec3(nOrigin.x, nOrigin.y, nOrigin.z),
                glm::vec3(nDirection.x, nDirection.y, nDirection.z),
                ray.Time()
        };

        if(!m_object->Hit(rotatedRay, tMin, tMax, record))
            return false;

        glm::vec4 nPoint  = m_rotationMatrix * glm::vec4(record.point, 0);
        glm::vec4 nNormal = m_rotationMatrix * glm::vec4(record.normal, 1);

        record.point = glm::vec3(nPoint.x, nPoint.y, nPoint.z);
        record.SetFaceNormal(rotatedRay, glm::vec3(nNormal.x, nNormal.y, nNormal.z));

        return true;
    }

    template<uint8_t axis>
    bool Rotation<axis>::BoundingBox(const double t0, const double t1, AABB& box) const
    {
        box = m_boundingBox;
        return m_haveBoundingBox;
    }
}
