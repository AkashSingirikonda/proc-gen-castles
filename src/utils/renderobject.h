#pragma once

#include "scene/sceneobject.h"
#include "scene/sceneprimitive.h"
#include "utils/scenedata.h"

/*
 * After a scene is generated its scene objects are converted into render objects.
 * These store the global transform, normal inverse transform, and relevant scene primitive / texture
 */
class RenderObject
{
public:
    RenderObject(glm::mat4 globalTransform, ScenePrimitive* scenePrimitive);

    glm::mat4 ctm;
    glm::mat4 normInv;

    ScenePrimitive* primitive;
    SceneMaterial* material;
};

