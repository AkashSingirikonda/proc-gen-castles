#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "textures/texturetypes.h"
#include "primitivetypes.h"

class SceneNode
{
public:
    SceneNode();
    ~SceneNode();

    // used during construction to keep track of transforms between SceneNodes and SceneObjects
    glm::mat4 relativeTransform;

    // transient variable to compute global transform for scene objects
    glm::mat4 ctm;

private:
    std::vector<SceneNode*> children;
};


class SceneObject : public SceneNode
{
public:
    SceneObject();
    ~SceneObject();

private:
    TextureType texture;
    PrimitiveType primitive;
};
