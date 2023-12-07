#pragma once

#include "scene/sceneobject.h"
#include "scene/sceneprimitive.h"


/*
 * After a scene is generated its scene objects are converted into render objects.
 * These store the global transform, normal inverse transform, and relevant scene primitive / texture
 */
class RenderObject
{
public:
    RenderObject(SceneObject* source);

    glm::mat4 ctm;
    glm::mat4 normInv;

    ScenePrimitive* primitive;
};

