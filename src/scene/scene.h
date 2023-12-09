#pragma once

#include <vector>

#include "sceneobject.h"


class Scene
{
public:
    Scene();
    ~Scene();

    SceneNode* root;
};
