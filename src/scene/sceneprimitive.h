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
    ScenePrimitive(){};
    ~ScenePrimitive(){};

    GLuint VAO_name;
    GLuint VBO_name;
    std::vector<float> VBO;

    virtual void generate(int k1, int k2){};

    virtual PrimitiveType getPrimitiveType() = 0;

private:

    std::vector<glm::vec3> points;
    std::vector<glm::vec3> norms;
    std::vector<glm::vec2> uvs;
};

class PrimitivePlane : public ScenePrimitive
{
    PrimitiveType getPrimitiveType() override { return PrimitiveType::PRIMITIVE_PLANE; };
    void generate(int k1, int k2) override;
};

class PrimitiveCube : public ScenePrimitive
{
    PrimitiveType getPrimitiveType() override { return PrimitiveType::PRIMITIVE_CUBE; };
    void generate(int k1, int k2) override;
};
class PrimitiveCone : public ScenePrimitive
{
    PrimitiveType getPrimitiveType() override { return PrimitiveType::PRIMITIVE_CONE; };
    void generate(int k1, int k2) override;
};


// TODO add more scene primitives
// The most useful will likely be a flat plane
