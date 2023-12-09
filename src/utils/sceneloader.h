#pragma once

#include <vector>
#include <map>

#include "scene/scene.h"
#include "scene/sceneprimitive.h"
#include "renderobject.h"

class SceneLoader{
public:
    static void GetRenderObjectsForScene(Scene& scene, std::map<PrimitiveType, ScenePrimitive*>& primitiveTypes, std::vector<RenderObject*>& renderObjects){
        // TODO

        // careful to not create more primitive types than necessary
    }
};
