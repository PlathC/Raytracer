//
// Created by Platholl on 05/07/2020.
//

#ifndef RAYTRACER_BVHNODE_HPP
#define RAYTRACER_BVHNODE_HPP

#include <algorithm>
#include <stdexcept>

#include "Raytracer/Math/Core.hpp"

#include "Raytracer/Object/Hittable.hpp"
#include "Raytracer/Object/Environment.hpp"

namespace rt
{
    class BVHNode : public Hittable
    {
    public:
        BVHNode() = default;
        BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, const size_t start, const size_t end,
                const double time0, const double time1);
        BVHNode(rt::Environment& environment, const double time0, const double time1);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;

    private:
        std::shared_ptr<Hittable> m_left;
        std::shared_ptr<Hittable> m_right;
        AABB m_box;
    };

    // Comparison helper functions to be able to sort Hittable list in order to build BVH
    inline bool CompareBox(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, const uint8_t axis)
    {
        AABB boxA;
        AABB boxB;

        if(!a->BoundingBox(0, 0, boxA) || !b->BoundingBox(0, 0, boxB))
            throw std::runtime_error("No bounding box available");

        return boxA.Minimum()[axis] < boxB.Minimum()[axis];
    }

    inline bool CompareBoxX(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
    {
        return CompareBox(a, b, 0);
    }

    inline bool CompareBoxY(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
    {
        return CompareBox(a, b, 1);
    }

    inline bool CompareBoxZ(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b)
    {
        return CompareBox(a, b, 2);
    }
}

#endif //RAYTRACER_BVHNODE_HPP
