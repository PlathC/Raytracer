//
// Created by Platholl on 05/07/2020.
//

#ifndef RAYTRACER_OBJLOADER_HPP
#define RAYTRACER_OBJLOADER_HPP

#include "Raytracer/Utils/MeshLoader.hpp"

namespace rt
{
    class ObjLoader : public MeshLoader
    {
    public:
        ObjLoader(const std::string& file) : MeshLoader(file) {}

        std::unique_ptr<rt::TriangleMesh> Parse() const override;

        virtual ~ObjLoader() {}
    };
}

#endif //RAYTRACER_OBJLOADER_HPP
