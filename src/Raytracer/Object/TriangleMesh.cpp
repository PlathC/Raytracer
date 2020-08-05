//
// Created by Platholl on 03/07/2020.
//

#include "Raytracer/Material/Material.hpp"
#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/SolidColor.hpp"
#include "Raytracer/Math/Math.hpp"
#include "Raytracer/Object/TriangleMesh.hpp"

namespace rt
{
    TriangleMesh::TriangleMesh(const MeshSettings& settings):
        m_trianglesNumber(0),
        m_vertices(settings.vertices.size()),
        m_normals(settings.normals),
        m_materialIndexes(),
        m_materials(settings.materials)
    {
        for(size_t i = 0; i < settings.vertices.size(); i++)
        {
            // TODO: Handle vertex color
            m_vertices[i] = Vertex(settings.vertices[i], glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
        }

        // Compute triangles number
        for(uint32_t i = 0; i < settings.facesNumber; ++i)
        {
            // We use GL_TRIANGLE_FAN type of triangulation
            m_trianglesNumber += settings.facesIndexes[i] - 2;
        }

        m_trianglesIndexes.resize(m_trianglesNumber * 3);
        m_triangles.reserve(m_trianglesNumber);

        if(m_normals.empty())
            ComputeNormals(settings);

        uint32_t l = 0;
        m_materialIndexes.reserve(m_trianglesNumber);
        for(uint32_t i = 0, k = 0; i < settings.facesNumber; ++i)
        {
            for(uint32_t j = 0; j < settings.facesIndexes[i] - 2; ++j)
            {
                uint32_t i1 = settings.verticesIndexes[k];
                uint32_t i2 = settings.verticesIndexes[k + j + 1];
                uint32_t i3 = settings.verticesIndexes[k + j + 2];

                m_trianglesIndexes[l]     = i1;
                m_trianglesIndexes[l + 1] = i2;
                m_trianglesIndexes[l + 2] = i3;

                if(m_normals.empty())
                {
                    auto nTriangle = std::make_shared<Triangle>(m_vertices[i1],
                                                                m_vertices[i2],
                                                                m_vertices[i3],
                                                                m_materials[settings.materialIndexes[i]]);
                    m_triangles.emplace_back(nTriangle);
                }
                else
                {
                    uint32_t in1 = settings.normalsIndexes[k];
                    uint32_t in2 = settings.normalsIndexes[k + j + 1];
                    uint32_t in3 = settings.normalsIndexes[k + j + 2];

                    m_vertices[i1].normal = m_normals[in1];
                    m_vertices[i2].normal = m_normals[in2];
                    m_vertices[i2].normal = m_normals[in3];
                    m_triangles.emplace_back(std::make_shared<rt::Triangle>(
                            m_vertices[i1],
                            m_vertices[i2],
                            m_vertices[i3],
                            m_materials[settings.materialIndexes[i]]
                    ));
                }
                m_materialIndexes.push_back(settings.materialIndexes[i]);
                l += 3;
            }
            k += settings.facesIndexes[i];
        }
    }

    void TriangleMesh::ComputeNormals(const MeshSettings& settings)
    {
        uint32_t l = 0;
        for(uint32_t i = 0, k = 0; i < settings.facesNumber; ++i)
        {
            for(uint32_t j = 0; j < settings.facesIndexes[i] - 2; ++j)
            {
                uint32_t i1 = settings.verticesIndexes[k];
                uint32_t i2 = settings.verticesIndexes[k + j + 1];
                uint32_t i3 = settings.verticesIndexes[k + j + 2];

                m_trianglesIndexes[l]     = i1;
                m_trianglesIndexes[l + 1] = i2;
                m_trianglesIndexes[l + 2] = i3;

                Triangle::ComputeNormal(
                        m_vertices[i1],
                        m_vertices[i2],
                        m_vertices[i3]);
                l += 3;
            }
            k += settings.facesIndexes[i];
        }

        for(auto& vertex : m_vertices)
        {
            vertex.normal = glm::normalize(vertex.normal);
        }
    }

    bool TriangleMesh::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
    {
        double closestT = tMax;
        bool hit = false;
        HitRecord tempRecord{};

        uint32_t faceCounter = 0;
        for(const auto& triangle : m_triangles)
        {
            if(triangle->Hit(ray, tMin, tMax, tempRecord) && tempRecord.t < closestT)
            {
                record = tempRecord;
                closestT = record.t;
                hit = true;

                record.material = m_materials[m_materialIndexes[faceCounter]].get();
            }
            faceCounter++;
        }

        return hit;
    }

    bool TriangleMesh::BoundingBox(const double /*t0*/, const double /*t1*/, AABB& box) const
    {
        glm::vec3 min{std::numeric_limits<float>::infinity(),
                      std::numeric_limits<float>::infinity(),
                      std::numeric_limits<float>::infinity()};
        glm::vec3 max{0,0,0};

        for(const auto& vertex : m_vertices)
        {
            for(uint8_t c = 0; c < 3; c++)
            {
                min[c] = std::fmin(min[c], vertex.position[c]);
                max[c] = std::fmax(max[c], vertex.position[c]);
            }
        }
        box = AABB(min, max);
        return true;
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::CreateSphere(float rad, uint32_t divs)
    {
        // Based on https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-polygon-mesh/Ray-Tracing%20a%20Polygon%20Mesh-part-1

        const uint32_t verticesNumber = (divs - 1) * divs + 2;
        auto points  = std::vector<glm::vec3>(verticesNumber);
        auto normals = std::vector<glm::vec3>(verticesNumber);
        //auto st    = std::vector<Vec2>(verticesNumber);

        float u = static_cast<float>(-rt::Pi) / 2.f;
        auto v = static_cast<float>(-rt::Pi);
        const float du = static_cast<float>(rt::Pi) / divs;
        const float dv = 2.f * static_cast<float>(rt::Pi) / divs;

        points[0] = normals[0] = glm::vec3(0, -rad, 0);
        uint32_t k = 1;
        for(uint32_t i = 0; i < divs - 1; ++i)
        {
            u += du;
            v = static_cast<float>(-rt::Pi);
            for(uint32_t j = 0;j < divs; ++j)
            {
                float x = rad * std::cos(u) * std::cos(v);
                float y = rad * std::sin(u);
                float z = rad * std::cos(u) * std::sin(v);

                points[k] = normals[k] = glm::vec3(x, y, z);
                // st[k].x = u / M_PI + 0.5;
                // st[k].y = v * 0.5 / M_PI + 0.5;
                v += dv;
                k++;
            }
        }

        points[k] = normals[k] = glm::vec3{0, rad, 0};

        uint32_t polyNumber = divs * divs;
        auto faceIndexes   = std::vector<uint32_t>(polyNumber);
        auto verticesIndex = std::vector<uint32_t>((6 + (divs - 1) * 4) * divs);
        auto normalsIndex  = std::vector<uint32_t>((6 + (divs - 1) * 4) * divs);
        std::vector<std::shared_ptr<Material>> materials { polyNumber};
        auto materialIndexes = std::vector<uint32_t>(polyNumber, 0);

        for(size_t i = 0; i < materials.size(); i++)
        {
            materials[i] = std::make_shared<rt::Lambertian>(
                    std::make_shared<rt::SolidColor>(glm::vec3{rt::Random<float>(), rt::Random<float>(), rt::Random<float>() }));
            materialIndexes[i] = static_cast<uint32_t>(i);
        }

        uint32_t vid = 1, numV = 0, l = 0;
        k = 0;
        for(uint32_t i = 0; i < divs; ++i)
        {
            for(uint32_t j = 0; j < divs; j++)
            {
                if(i == 0)
                {
                    faceIndexes[k++] = 3;

                    verticesIndex[l]     = normalsIndex[l]     = 0;
                    verticesIndex[l + 1] = normalsIndex[l + 1] = j + vid;
                    verticesIndex[l + 2] = normalsIndex[l + 2] = (j == (divs - 1)) ? vid : j + vid + 1;
                    l += 3;
                }
                else if(i == divs - 1)
                {
                    faceIndexes[k++] = 3;

                    verticesIndex[l]     = normalsIndex[l]     = j + vid + 1 - divs;
                    verticesIndex[l + 1] = normalsIndex[l + 1] = vid + 1;
                    verticesIndex[l + 2] = normalsIndex[l + 2] = (j == (divs - 1)) ? vid + 1 - divs : j + vid + 2 - divs;

                    l += 3;
                }
                else
                {
                    faceIndexes[k++] = 4;

                    verticesIndex[l]     = normalsIndex[l]     = j + vid + 1 - divs;
                    verticesIndex[l + 1] = normalsIndex[l + 1] = j + vid + 1;
                    verticesIndex[l + 2] = normalsIndex[l + 2] = (j == (divs - 1)) ? vid + 1 : j + vid + 2;
                    verticesIndex[l + 3] = normalsIndex[l + 3] = (j == (divs - 1)) ? vid + 1 - divs : j + vid + 2 - divs;
                    l += 4;
                }
                numV++;
            }
            vid = numV;
        }

        return std::make_shared<TriangleMesh>(MeshSettings{polyNumber, faceIndexes, verticesIndex, points,
                                              normalsIndex, normals, materialIndexes, materials});
    }

    [[nodiscard]] std::vector<std::shared_ptr<rt::IHittable>> TriangleMesh::Objects() const
    {
        std::vector<std::shared_ptr<rt::IHittable>> result;
        result.reserve(m_triangles.size());
        for(const auto& triangle : m_triangles)
        {
            result.push_back(triangle);
        }

        return result;
    }

    std::size_t TriangleMesh::Size() const
    {
        return m_trianglesNumber;
    }
}