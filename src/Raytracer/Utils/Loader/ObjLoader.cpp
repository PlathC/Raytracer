//
// Created by Platholl on 05/07/2020.
//

#include <array>
#include <filesystem>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Raytracer/Material/Lambertian.hpp"
#include "Raytracer/Material/SolidColor.hpp"
#include "Raytracer/Material/PerlinTexture.hpp"

#include "Raytracer/Utils/Loader/ObjLoader.hpp"

namespace fs = std::filesystem;

namespace rt
{
    std::shared_ptr<rt::TriangleMesh> ObjLoader::Parse() const
    {
        tinyobj::attrib_t meshAttributes;
        std::vector<tinyobj::shape_t> meshShapes;
        std::vector<tinyobj::material_t> meshMaterials;
        std::string err;
        auto path = fs::path(m_file);
        const std::string materialFolder = path.parent_path().string() + "/";
        bool ret = tinyobj::LoadObj(&meshAttributes, &meshShapes, &meshMaterials, &err, m_file.c_str(), materialFolder.c_str());


        if (!ret)
        {
            throw std::runtime_error("Error while parsing obj file : " + err);
        }
        else if(!err.empty())
        {
            std::cerr << err << "\n";
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

        // Create Materials
        std::vector<uint32_t> materialIndexes;

        //size_t vertexCounter = 0;
        for (auto & meshShape : meshShapes)
        {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < meshShape.mesh.num_face_vertices.size(); f++)
            {
                uint8_t verticesNumber = meshShape.mesh.num_face_vertices[f];
                faceIndex.push_back(verticesNumber);

                // Loop over vertices in the face.
                for (size_t v = 0; v < verticesNumber; v++)
                {
                    // access to vertex
                    tinyobj::index_t idx = meshShape.mesh.indices[index_offset + v];
                    vertexIndex.push_back(idx.vertex_index);
                    normalIndex.push_back(idx.normal_index);

                    // TODO : Handle text coordinates + materials
                }
                index_offset += verticesNumber;
                if(meshShape.mesh.material_ids[f] < 0)
                    materialIndexes.push_back(0);
                else
                    materialIndexes.push_back(meshShape.mesh.material_ids[f]);

                // TODO : Same
                numFaces++;
            }
        }

        auto materials = std::vector<std::shared_ptr<Material>>(meshMaterials.size());
        size_t materialIterator = 0;
        for(auto& material : meshMaterials)
        {
            glm::vec3 color = {
                    material.diffuse[0],
                    material.diffuse[1],
                    material.diffuse[2],
            };
            materials[materialIterator++] = std::make_shared<rt::Lambertian>(std::make_unique<SolidColor>(color));
        }

        if(materials.empty())
        {
            materials.push_back(std::make_shared<rt::Lambertian>(std::make_unique<SolidColor>(glm::vec3(0.5, 0.5, 0.5))));
        }

        return std::make_shared<rt::TriangleMesh>(MeshSettings{numFaces, faceIndex, vertexIndex, vertices, normalIndex, normals,
                materialIndexes, materials});
    }
}