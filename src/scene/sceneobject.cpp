#include "sceneobject.h"

SceneObject::SceneObject()
{

}

SceneObject::SceneObject(PrimitiveType primitiveType, TextureType textureType)
{
    primitive = primitiveType;
    texture = textureType;
}

SceneLight::SceneLight()
{

}

SceneLight::SceneLight(SceneLightData sceneLightData)
{
    lightData = sceneLightData;
}

SceneNode::SceneNode()
{

}
