#pragma once

#include <vector>

#include "sceneobject.h"
#include "scenedata.h"

class Scene
{
public:
    Scene();
    ~Scene();

    SceneNode* root;

    SceneGlobalData globalData;
    SceneCameraData cameraData;
};
