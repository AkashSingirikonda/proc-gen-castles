#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "primitivetypes.h"

/*
 * Component of a scene like a single triangle or some basic shape (cube, cone, etc.)
 */
class ScenePrimitive
{
public:
    ScenePrimitive();
    ~ScenePrimitive();

    GLuint VAO_name;
    GLuint VBO_name;
    std::vector<float> VBO;

    void generate(int k1, int k2){}; // TODO generate points, norms, and UVs based on parameters

    virtual PrimitiveType getPrimitiveType();

private:

    std::vector<glm::vec3> points;
    std::vector<glm::vec3> norms;
    std::vector<glm::vec2> uvs;
};
