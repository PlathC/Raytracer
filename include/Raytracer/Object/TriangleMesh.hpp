//
// Created by Platholl on 03/07/2020.
//

#ifndef RAYTRACER_TRIANGLEMESH_HPP
#define RAYTRACER_TRIANGLEMESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include "Raytracer/Object/IHittable.hpp"
#include "Raytracer/Object/Environment.hpp"
#include "Raytracer/Object/Triangle.hpp"

namespace rt
{
    struct MeshSettings
    {
        uint32_t facesNumber;
        std::vector<uint32_t> facesIndexes;
        std::vector<uint32_t> verticesIndexes;
        std::vector<glm::vec3> vertices;
        std::vector<uint32_t> normalsIndexes;
        std::vector<glm::vec3> normals;
        std::vector<uint32_t> materialIndexes;
        std::vector<std::shared_ptr<Material>> materials;
    };

    class TriangleMesh : public ICollection
    {
    public:
        explicit TriangleMesh(const MeshSettings& settings);

        void ComputeNormals(const MeshSettings& settings);

        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
        bool BoundingBox(const double t0, const double t1, AABB& box) const override;

        [[nodiscard]] std::vector<std::shared_ptr<rt::IHittable>> Objects() const override;
        std::size_t Size() const override;

        static std::shared_ptr<TriangleMesh> CreateSphere(float rad, uint32_t divs);

    private:
        uint32_t m_trianglesNumber;

        std::vector<uint32_t> m_trianglesIndexes;
        std::vector<rt::Vertex> m_vertices;
        std::vector<glm::vec3> m_normals;
        std::vector<std::shared_ptr<rt::Triangle>> m_triangles;

        // TODO: Add support of st coordinates
        // std::vector<Vec2> m_stCoordinates

        std::vector<uint32_t> m_materialIndexes;
        std::vector<std::shared_ptr<Material>> m_materials;
    };
}

#endif //RAYTRACER_TRIANGLEMESH_HPP
