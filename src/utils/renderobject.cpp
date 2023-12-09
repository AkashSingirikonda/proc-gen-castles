#include "renderobject.h"

RenderObject::RenderObject(glm::mat4 globalTransform, ScenePrimitive* scenePrimitive)
{
    primitive = scenePrimitive;

    ctm = globalTransform;
}
