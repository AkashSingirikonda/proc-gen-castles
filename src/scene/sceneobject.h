#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "textures/texturetypes.h"
#include "primitivetypes.h"
#include "scenedata.h"

class SceneObject
{
public:
    SceneObject();
    ~SceneObject();

    SceneObject(PrimitiveType primitiveType, TextureType textureType);

    glm::mat4 transform = glm::mat4(1);

    PrimitiveType primitive;
    TextureType texture;
};

class SceneLight
{
public:
    SceneLight();
    ~SceneLight();

    SceneLight(SceneLightData sceneLightData);

    glm::mat4 transform = glm::mat4(1);

    SceneLightData lightData;
};

class SceneNode
{
public:
    SceneNode();
    ~SceneNode();

    glm::mat4 transform = glm::mat4(1);

    std::vector<SceneNode*> children;
    std::vector<SceneObject*> objects;
    std::vector<SceneLight*> lights;
};


