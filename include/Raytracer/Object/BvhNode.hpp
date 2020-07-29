//
// Created by Platholl on 05/07/2020.
//

#ifndef RAYTRACER_BVHNODE_HPP
#define RAYTRACER_BVHNODE_HPP

#include <algorithm>
#include <stdexcept>

#include "Raytracer/Math/Math.hpp"

#include "Raytracer/Object/IHittable.hpp"
#include "Raytracer/Object/ICollection.hpp"

namespace rt
{
    class BVHNode : public IHittable
    {
    public:
        BVHNode() = default;
        BVHNode(const std::vector<std::shared_ptr<IHittable>>& objects, const size_t start, const size_t end,
                const double time0, const double time1);
        BVHNode(const rt::ICollection& environment, const double time0, const double time1);

        virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        virtual bool BoundingBox(const double t0, const double t1, AABB& box) const override;

    private:
        std::shared_ptr<IHittable> m_left;
        std::shared_ptr<IHittable> m_right;
        AABB m_box;
    };

    // Comparison helper functions to be able to sort IHittable list in order to build BVH
    inline bool CompareBox(std::shared_ptr<IHittable> a, std::shared_ptr<IHittable> b, const uint8_t axis)
    {
        AABB boxA;
        AABB boxB;

        if(!a->BoundingBox(0, 0, boxA) || !b->BoundingBox(0, 0, boxB))
            throw std::runtime_error("No bounding box available");

        return boxA.Minimum()[axis] < boxB.Minimum()[axis];
    }

    inline bool CompareBoxX(std::shared_ptr<IHittable> a, std::shared_ptr<IHittable> b)
    {
        return CompareBox(a, b, 0);
    }

    inline bool CompareBoxY(std::shared_ptr<IHittable> a, std::shared_ptr<IHittable> b)
    {
        return CompareBox(a, b, 1);
    }

    inline bool CompareBoxZ(std::shared_ptr<IHittable> a, std::shared_ptr<IHittable> b)
    {
        return CompareBox(a, b, 2);
    }
}

#endif //RAYTRACER_BVHNODE_HPP
