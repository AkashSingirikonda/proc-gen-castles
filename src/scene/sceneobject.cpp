#include "sceneobject.h"

SceneObject::SceneObject()
{

}

SceneObject::SceneObject(PrimitiveType primitiveType, TextureType textureType)
{
    primitive = primitiveType;
    texture = textureType;
}

SceneNode::SceneNode()
{

}
