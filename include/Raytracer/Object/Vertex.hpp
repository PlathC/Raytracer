//
// Created by Platholl on 05/07/2020.
//

#ifndef RAYTRACER_VERTEX_HPP
#define RAYTRACER_VERTEX_HPP

#include <glm/vec3.hpp>

namespace rt
{
    struct Vertex
    {
        Vertex() : position(), normal() {}
        Vertex(const glm::vec3& pos, const glm::vec3& norm) : position(pos), normal(norm) {}

        glm::vec3 position;
        glm::vec3 normal;
    };
}

#endif //RAYTRACER_VERTEX_HPP
