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
        Vertex(const glm::vec3& pos,
               const glm::vec3& norm = {0, 0, 0},
               const glm::vec3& col = {0, 0, 0}) :
           position(pos),
           normal(norm),
           color(col)
       {}

        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
    };
}

#endif //RAYTRACER_VERTEX_HPP
