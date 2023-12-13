#include "sceneobject.h"

SceneObject::SceneObject(PrimitiveType primitiveType, TextureType textureType)
{
    primitive = primitiveType;
    texture = textureType;
}

SceneLight::SceneLight(SceneLightData sceneLightData)
{
    lightData = sceneLightData;
}
