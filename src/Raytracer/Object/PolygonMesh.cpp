//
// Created by Platholl on 03/07/2020.
//

#include "Raytracer/Object/PolygonMesh.hpp"

namespace rt
{
    PolygonMesh::PolygonMesh(const uint32_t facesNumber, const std::vector<rt::Vec3f>& vertices,
            const std::vector<uint32_t>& facesIndexes, const std::vector<uint32_t>& vertexIndexes) :
        m_facesNumber(facesNumber),
        m_vertices(vertices),
        m_faceIndexes(facesIndexes),
        m_vertexIndexes(vertexIndexes)
    {}

    bool PolygonMesh::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {

        return false;
    }
}