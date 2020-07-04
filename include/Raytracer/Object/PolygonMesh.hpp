//
// Created by Platholl on 03/07/2020.
//

#ifndef RAYTRACER_MESH_HPP
#define RAYTRACER_MESH_HPP

#include "Raytracer/Math/Vec3.hpp"
#include "Raytracer/Object/Hittable.hpp"

namespace rt
{
    class Mesh : public Hittable
    {
    public:
        Mesh(uint32_t faceNumber, const std::vector<rt::Vec3>& vertices, const std::vector<uint32_t>& faceIndexes,
                const std::vector<uint32_t>& vertexIndexes);

        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

    private:
        uint32_t m_facesNumber;

        std::vector<rt::Vec3> m_vertices;
        std::vector<uint32_t> m_faceIndexes;
        std::vector<uint32_t> m_vertexIndexes;
    };
}

#endif //RAYTRACER_MESH_HPP
