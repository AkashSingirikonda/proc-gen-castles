#include "sceneprimitive.h"

void pushVec3(glm::vec3 vec, std::vector<float>* data)
{
    data->push_back(vec.x);
    data->push_back(vec.y);
    data->push_back(vec.z);
}

void pushPointAndNorm3(glm::vec3 p, glm::vec3 n, std::vector<float>* data)
{
    pushVec3(p, data);
    pushVec3(n, data);
}

void makeFace(std::vector<float>* data, glm::vec3 topLeft, glm::vec3 topRight, glm::vec3 bottomLeft, glm::vec3 bottomRight)
{
    glm::vec3 n = glm::normalize(glm::cross(bottomLeft - topLeft, topRight - topLeft));

    pushPointAndNorm3(topLeft, n, data);
    pushPointAndNorm3(bottomLeft, n, data);
    pushPointAndNorm3(bottomRight, n, data);

    pushPointAndNorm3(topLeft, n, data);
    pushPointAndNorm3(bottomRight, n, data);
    pushPointAndNorm3(topRight, n, data);
}

void PrimitivePlane::generate(int k1, int k2)
{
    VBO.clear();

    makeFace(&VBO,
             glm::vec3( 0.5f, 0.5f,  0.5f),
             glm::vec3(-0.5f, 0.5f,  0.5f),
             glm::vec3( 0.5f, 0.5f, -0.5f),
             glm::vec3(-0.5f, 0.5f, -0.5f));
}

void PrimitiveCube::generate(int k1, int k2)
{
    VBO.clear();

    makeFace(&VBO,
             glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3( 0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f, -0.5f, 0.5f),
             glm::vec3( 0.5f, -0.5f, 0.5f));

    makeFace(&VBO,
             glm::vec3( 0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f,  0.5f, -0.5f),
             glm::vec3( 0.5f, -0.5f, -0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f));

    makeFace(&VBO,
             glm::vec3( 0.5f, 0.5f,  0.5f),
             glm::vec3(-0.5f, 0.5f,  0.5f),
             glm::vec3( 0.5f, 0.5f, -0.5f),
             glm::vec3(-0.5f, 0.5f, -0.5f));

    makeFace(&VBO,
             glm::vec3(-0.5f, -0.5f,  0.5f),
             glm::vec3( 0.5f, -0.5f,  0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f),
             glm::vec3( 0.5f, -0.5f, -0.5f));

    makeFace(&VBO,
             glm::vec3(0.5f, -0.5f,  0.5f),
             glm::vec3(0.5f,  0.5f,  0.5f),
             glm::vec3(0.5f, -0.5f, -0.5f),
             glm::vec3(0.5f,  0.5f, -0.5f));

    makeFace(&VBO,
             glm::vec3(-0.5f,  0.5f,  0.5f),
             glm::vec3(-0.5f, -0.5f,  0.5f),
             glm::vec3(-0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f, -0.5f, -0.5f));
}
