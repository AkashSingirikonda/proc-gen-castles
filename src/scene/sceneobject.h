#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "textures/texturetypes.h"
#include "primitivetypes.h"


class SceneObject
{
public:
    SceneObject();
    ~SceneObject();

    TextureType texture;
    PrimitiveType primitive;
    //TODO add material which we need to construct RenderObject
};

class SceneNode
{
public:
    SceneNode();
    ~SceneNode();

    glm::mat4 transform;

    std::vector<SceneNode*> children;
    std::vector<SceneObject*> objects;
};


