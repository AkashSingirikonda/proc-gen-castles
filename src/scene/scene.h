#include <vector>


#include "sceneobject.h"


class Scene
{
public:
    Scene();
    ~Scene();


private:

    std::vector<SceneObject*> sceneObjects;
};