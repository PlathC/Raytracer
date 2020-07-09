//
// Created by Platholl on 05/07/2020.
//

#include "Raytracer/Utils/Loader/ObjLoader.hpp"

#include <array>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/SolidColor.hpp"
#include "Raytracer/Material/PerlinTexture.hpp"

namespace rt
{
    std::shared_ptr<rt::TriangleMesh> ObjLoader::Parse() const
    {
        tinyobj::attrib_t meshAttributes;
        std::vector<tinyobj::shape_t> meshShapes;
        std::vector<tinyobj::material_t> meshMaterials;
        std::string err;

        bool ret = tinyobj::LoadObj(&meshAttributes, &meshShapes, &meshMaterials, &err,m_file.c_str());

        if (!ret)
        {
            throw std::runtime_error("Error while parsing obj file : " + err);
        }

        uint32_t numFaces = 0;
        std::vector<uint32_t> faceIndex;

        auto vertexIndex = std::vector<uint32_t>();
        auto normalIndex = std::vector<uint32_t>();
        auto vertices    = std::vector<glm::vec3>(meshAttributes.vertices.size() / 3);
        auto normals     = std::vector<glm::vec3>(meshAttributes.normals.size() / 3);

        for(size_t i = 0; i < meshAttributes.vertices.size() / 3; i++)
        {
            vertices[i] = glm::vec3(meshAttributes.vertices[3 * i + 0],
                    meshAttributes.vertices[3 * i + 1],
                    meshAttributes.vertices[3 * i + 2]);
        }

        for(size_t i = 0; i < meshAttributes.normals.size() / 3; i++)
        {
            normals[i] = glm::vec3(meshAttributes.normals[3 * i + 0],
                                   meshAttributes.normals[3 * i + 1],
                                   meshAttributes.normals[3 * i + 2]);
        }

        size_t vertexCounter = 0;
        for (size_t s = 0; s < meshShapes.size(); s++)
        {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < meshShapes[s].mesh.num_face_vertices.size(); f++)
            {
                uint8_t verticesNumber = meshShapes[s].mesh.num_face_vertices[f];
                faceIndex.push_back(verticesNumber);

                // Loop over vertices in the face.
                for (size_t v = 0; v < verticesNumber; v++)
                {
                    // access to vertex
                    tinyobj::index_t idx = meshShapes[s].mesh.indices[index_offset + v];
                    vertexIndex.push_back(idx.vertex_index);
                    normalIndex.push_back(idx.normal_index);

                    // TODO : Handle text coordinates + materials
                }
                index_offset += verticesNumber;

                // TODO : Same
                numFaces++;
            }
        }

        // Create Materials
        std::vector<uint32_t> materialIndexes = std::vector<uint32_t>(numFaces, 0);
        auto materials = std::vector<std::shared_ptr<Material>>(1);
        materials[0] = std::make_shared<rt::Lambertian>(std::make_unique<PerlinTexture>(4));

        return std::make_shared<rt::TriangleMesh>(MeshSettings{numFaces, faceIndex, vertexIndex, vertices, normalIndex, normals,
                materialIndexes, materials});
    }
}