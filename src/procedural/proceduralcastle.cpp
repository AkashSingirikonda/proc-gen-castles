#include "proceduralcastle.h"

ProceduralCastle::ProceduralCastle()
{

}



void ProceduralCastle::generateScene(Scene& scene)
{
    // TODO
    SceneNode* root = new SceneNode();
    SceneObject* cube = new SceneObject(PrimitiveType::PRIMITIVE_CUBE, TextureType::TEXTURE_STONE);
    root->objects.push_back(cube);
}
