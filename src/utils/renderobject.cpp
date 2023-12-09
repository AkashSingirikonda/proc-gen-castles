#include "renderobject.h"

RenderObject::RenderObject(glm::mat4 globalTransform, ScenePrimitive* scenePrimitive)
{
    primitive = scenePrimitive;

    ctm = globalTransform;

    normInv = glm::inverse(globalTransform);
    normInv[3] = glm::vec4(0);
    normInv = glm::transpose(normInv);
}
