//
// Created by Platholl on 03/07/2020.
//

#ifndef RAYTRACER_TRIANGLEMESH_HPP
#define RAYTRACER_TRIANGLEMESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include "Raytracer/Object/Hittable.hpp"
#include "Raytracer/Object/Triangle.hpp"

namespace rt
{
    class TriangleMesh : public Hittable
    {
    public:
        TriangleMesh(const uint32_t facesNumber, const std::vector<uint32_t>& facesIndexes,
                     const std::vector<uint32_t>& verticesIndexes, const std::vector<glm::vec3>& vertices,
                     const std::vector<uint32_t>& normalsIndexes, const std::vector<glm::vec3>& normals,
                     const std::vector<uint32_t>& materialIndexes, std::vector<std::unique_ptr<Material>>&& materials);

        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

        static std::unique_ptr<TriangleMesh> CreateSphere(float rad, uint32_t divs);

    private:
        uint32_t m_trianglesNumber;

        std::vector<uint32_t> m_trianglesIndexes;
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec3> m_normals;
        std::vector<rt::Triangle> m_triangles;

        // TODO: Add support of st coordinates
        // std::vector<Vec2> m_stCoordinates

        std::vector<uint32_t> m_materialIndexes;
        std::vector<std::unique_ptr<Material>> m_materials;
    };
}

#endif //RAYTRACER_TRIANGLEMESH_HPP
