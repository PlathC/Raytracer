//
// Created by Platholl on 05/07/2020.
//

#ifndef RAYTRACER_MESHLOADER_HPP
#define RAYTRACER_MESHLOADER_HPP

#include <filesystem>
#include <string>

#include "Raytracer/Object/TriangleMesh.hpp"

namespace fs = std::filesystem;

namespace rt
{
    class MeshLoader
    {
    public:
        MeshLoader(const std::string& file) : m_file(file) {}

        virtual std::unique_ptr<rt::TriangleMesh> Parse() const = 0;

        virtual ~MeshLoader() {}

    protected:
        std::string m_file;
    };
}

#endif //RAYTRACER_LOADER_HPP
