//
// Created by Platholl on 03/07/2020.
//

#ifndef RAYTRACER_TRIANGLEMESH_HPP
#define RAYTRACER_TRIANGLEMESH_HPP

#include "Raytracer/Math/Vec3.hpp"
#include "Raytracer/Object/Hittable.hpp"
#include "Raytracer/Object/Triangle.hpp"

namespace rt
{
    class TriangleMesh : public Hittable
    {
    public:
        TriangleMesh(const uint32_t facesNumber, const std::vector<uint32_t>& facesIndexes,
                     const std::vector<uint32_t>& verticesIndexes, const std::vector<Vec3>& vertices,
                     const std::vector<Vec3>& normals, std::unique_ptr<Material>&& material);

        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

        static std::unique_ptr<TriangleMesh> CreateSphere(float rad, uint32_t divs);

    private:
        uint32_t m_trianglesNumber;

        std::vector<uint32_t> m_trianglesIndexes;
        std::vector<Vec3> m_vertices;
        std::vector<Vec3> m_normals;
        std::vector<rt::Triangle> m_triangles;

        // TODO: Add support of st coordinates
        // std::vector<Vec2> m_stCoordinates

        std::unique_ptr<Material> m_material;
    };
}

#endif //RAYTRACER_TRIANGLEMESH_HPP
