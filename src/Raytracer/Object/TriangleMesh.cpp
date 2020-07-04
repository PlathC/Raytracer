//
// Created by Platholl on 03/07/2020.
//

#include "Raytracer/Object/TriangleMesh.hpp"

#include "Raytracer/Material/Material.hpp"
#include "Raytracer/Material/Lambertian.hpp"

namespace rt
{
    TriangleMesh::TriangleMesh(const uint32_t facesNumber, const std::vector<uint32_t>& facesIndexes,
                               const std::vector<uint32_t>& verticesIndexes, const std::vector<Vec3f>& vertices,
                               const std::vector<Vec3f>& normals, std::unique_ptr<Material>&& material):
        m_trianglesNumber(0),
        m_vertices(vertices),
        m_normals(normals),
        m_material(std::move(material))
    {
        // Compute triangles number
        for(uint32_t i = 0; i < facesNumber; ++i)
        {
            // We use GL_TRIANGLE_FAN type of triangulation
            m_trianglesNumber += facesIndexes[i] - 2;
        }

        m_trianglesIndexes.resize(m_trianglesNumber * 3);
        m_triangles.reserve(m_trianglesNumber);

        uint32_t l = 0;
        uint32_t triangleIndex = 0;
        for(uint32_t i = 0, k = 0; i < facesNumber; ++i)
        {
            for(uint32_t j = 0; j < facesIndexes[i] - 2; ++j)
            {
                uint32_t i1 = verticesIndexes[k];
                uint32_t i2 = verticesIndexes[k + j + 1];
                uint32_t i3 = verticesIndexes[k + j + 2];
                m_trianglesIndexes[l]     = i1;
                m_trianglesIndexes[l + 1] = i2;
                m_trianglesIndexes[l + 2] = i3;

                if(normals.empty())
                {
                    m_triangles.emplace_back(Triangle{
                            m_vertices[i1],
                            m_vertices[i2],
                            m_vertices[i3],
                            std::make_unique<rt::Lambertian>(rt::Vec3f{rt::Random<float>(),
                                                         rt::Random<float>(),
                                                         rt::Random<float>()})
                    });
                }
                else
                {
                    m_triangles.emplace_back(Triangle{
                            m_vertices[i1],
                            m_vertices[i2],
                            m_vertices[i3],
                            m_normals[triangleIndex++],
                            std::make_unique<rt::Lambertian>(rt::Vec3f{
                                    rt::Random<float>(),
                                    rt::Random<float>(),
                                    rt::Random<float>()})
                    });
                }

                l += 3;
            }
            k += facesIndexes[i];
        }
    }

    bool TriangleMesh::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        double closestT = tMax;
        bool hit = false;
        HitRecord tempRecord;

        for(const auto& triangle : m_triangles)
        {
            if(triangle.Hit(ray, tMin, closestT, tempRecord))
            {
                record = tempRecord;
                closestT = record.t;
                hit = true;
            }
        }

        return hit;
    }

    std::unique_ptr<TriangleMesh> TriangleMesh::CreateSphere(float rad, uint32_t divs)
    {
        // Based on https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-polygon-mesh/Ray-Tracing%20a%20Polygon%20Mesh-part-1

        const uint32_t verticesNumber = (divs - 1) * divs + 2;
        auto points  = std::vector<Vec3f>(verticesNumber);
        auto normals = std::vector<Vec3f>(verticesNumber);
        //auto st    = std::vector<Vec2>(verticesNumber);

        float u = -rt::Pi / 2.f;
        float v = -rt::Pi;
        const float du = rt::Pi / divs;
        const float dv = 2 * rt::Pi / divs;

        points[0] = normals[0] = Vec3f(0, -rad, 0);
        uint32_t k = 1;
        for(uint32_t i = 0; i < divs - 1; ++i)
        {
            u += du;
            v = -rt::Pi;
            for(uint32_t j = 0;j < divs; ++j)
            {
                float x = rad * std::cos(u) * std::cos(v);
                float y = rad * std::sin(u);
                float z = rad * std::cos(u) * std::sin(v);

                points[k] = normals[k] = Vec3(x, y, z);
                // st[k].x = u / M_PI + 0.5;
                // st[k].y = v * 0.5 / M_PI + 0.5;
                v += dv;
                k++;
            }
        }

        points[k] = normals[k] = Vec3f(0, rad, 0);

        uint32_t polyNumber = divs * divs;
        auto faceIndexes   = std::vector<uint32_t>(polyNumber);
        auto verticesIndex = std::vector<uint32_t>((6 + (divs - 1) * 4) * divs);

        uint32_t vid = 1, numV = 0, l = 0;
        k = 0;
        for(uint32_t i = 0; i < divs; ++i)
        {
            for(uint32_t j = 0; j < divs; j++)
            {
                if(i == 0)
                {
                    faceIndexes[k++] = 3;

                    verticesIndex[l]     = 0;
                    verticesIndex[l + 1] = j + vid;
                    verticesIndex[l + 2] = (j == (divs - 1)) ? vid : j + vid + 1;
                    l += 3;
                }
                else if(i == divs - 1)
                {
                    faceIndexes[k++] = 3;

                    verticesIndex[l]     = j + vid + 1 - divs;
                    verticesIndex[l + 1] = vid + 1;
                    verticesIndex[l + 2] = (j == (divs - 1)) ? vid + 1 - divs : j + vid + 2 - divs;

                    l += 3;
                }
                else
                {
                    faceIndexes[k++] = 4;

                    verticesIndex[l]     = j + vid + 1 - divs;
                    verticesIndex[l + 1] = j + vid + 1;
                    verticesIndex[l + 2] = (j == (divs - 1)) ? vid + 1 : j + vid + 2;
                    verticesIndex[l + 3] = (j == (divs - 1)) ? vid + 1 - divs : j + vid + 2 - divs;
                    l += 4;
                }
                numV++;
            }
            vid = numV;
        }

        return std::make_unique<TriangleMesh>(polyNumber, faceIndexes, verticesIndex, points,
                normals, std::make_unique<rt::Lambertian>(rt::Vec3f{0.8, 0.1, 1.}));
    }
}