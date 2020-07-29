//
// Created by Platholl on 05/07/2020.
//

#include "Raytracer/Object/BvhNode.hpp"

namespace rt
{
    BVHNode::BVHNode(const std::vector<std::shared_ptr<IHittable>>& objects, const size_t start, const size_t end,
            const double time0, const double time1)
    {
        const auto axis = static_cast<uint8_t>(Random<int>(0, 2));
        auto comparator = (axis == 0) ? CompareBoxX
                        : (axis == 1) ? CompareBoxY
                        : CompareBoxZ;

        size_t objectSpan = end - start;
        if(objectSpan == 1)
        {
            m_left = m_right = objects[start];
        }
        else if(objectSpan == 2)
        {
            if(comparator(objects[start], objects[start + 1]))
            {
                m_left  = objects[start];
                m_right = objects[start + 1];
            }
            else
            {
                m_right = objects[start];
                m_left = objects[start + 1];
            }
        }
        else
        {
            auto workingVector = std::vector(objects);
            std::sort(workingVector.begin() + start, workingVector.begin() + end, comparator);

            size_t mid = start + static_cast<size_t>(std::floor(objectSpan / 2));
            m_left  = std::make_shared<BVHNode>(workingVector, start, mid, time0, time1);
            m_right = std::make_shared<BVHNode>(workingVector, mid, end, time0, time1);
        }

        AABB boxLeft, boxRight;

        if(!m_left->BoundingBox(time0, time1, boxLeft)
        || !m_right->BoundingBox(time0, time1, boxRight))
            throw std::runtime_error("No bounding box available");

        m_box = AABB(boxLeft, boxRight);
    }

    BVHNode::BVHNode(const rt::ICollection& collection, const double time0, const double time1):
            BVHNode(collection.Objects(), 0, collection.Size(), time0, time1)
    {
    }

    bool BVHNode::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        if(!m_box.Hit(ray, tMin, tMax)) return false;

        bool hitLeft  = m_left->Hit(ray, tMin, tMax, record);
        bool hitRight = m_right->Hit(ray, tMin, hitLeft ? record.t : tMax, record);

        return hitLeft || hitRight;
    }

    bool BVHNode::BoundingBox(const double /*t0*/, const double /*t1*/, AABB& box) const
    {
        box = m_box;
        return true;
    }
}