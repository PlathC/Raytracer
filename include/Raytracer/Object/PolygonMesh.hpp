//
// Created by Platholl on 03/07/2020.
//

#ifndef RAYTRACER_POLYGONMESH_HPP
#define RAYTRACER_POLYGONMESH_HPP

#include <vector>

#include <glm/glm.hpp>

#include "Raytracer/Object/Hittable.hpp"

namespace rt
{
    class PolygonMesh : public Hittable
    {
    public:
        PolygonMesh(const uint32_t facesNumber, const std::vector<glm::vec3>& vertices,
                    const std::vector<uint32_t>& faceIndexes, const std::vector<uint32_t>& vertexIndexes);

        bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;


    private:
        uint32_t m_facesNumber;

        std::vector<glm::vec3> m_vertices;
        std::vector<uint32_t> m_faceIndexes;
        std::vector<uint32_t> m_vertexIndexes;
    };
}

#endif //RAYTRACER_POLYGONMESH_HPP
