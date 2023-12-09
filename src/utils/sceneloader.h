#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "scene/scene.h"
#include "scene/sceneprimitive.h"
#include "renderobject.h"

class SceneLoader{
public:
    static void GetRenderObjectsForScene(Scene& scene, std::map<PrimitiveType, ScenePrimitive*>& primitiveTypes, std::vector<RenderObject*>& renderObjects){
        buildSceneRecursive(scene.root, glm::mat4(1), primitiveTypes, renderObjects);
    }


    static void buildSceneRecursive(SceneNode* node, glm::mat4 ctm, std::map<PrimitiveType, ScenePrimitive*>& primitiveTypes, std::vector<RenderObject*>& renderObjects){
        ctm = ctm * node->transform;

        for(SceneObject* sceneObject : node->objects){
            PrimitiveType primitiveType = sceneObject->primitive;

            if(!primitiveTypes.contains(primitiveType)){
                std::cout << "Encountered unknown primitive on load" << std::endl;
            }

            const auto& it = primitiveTypes.find(primitiveType);
            ScenePrimitive* primitive = it->second;

            RenderObject* renderObject = new RenderObject(sceneObject, primitive);
            renderObjects.push_back(renderObject);
        }

//        for(SceneLight* sceneLight : node->lights){
//            SceneLightData light;
//            light.id = sceneLight->id;
//            light.type = sceneLight->type;
//            light.color = sceneLight->color;
//            light.function = sceneLight->function;
//            light.pos = ctm[3];
//            light.dir = ctm * sceneLight->dir;
//            light.penumbra = sceneLight->penumbra;
//            light.angle = sceneLight->angle;
//            light.width = sceneLight->width;
//            light.height = sceneLight->height;
//            renderData.lights.push_back(light);
//        }

        if(node->children.size() <= 0){
            return;
        }

        for(SceneNode* child : node->children){
            buildSceneRecursive(child, ctm, primitiveTypes, renderObjects);
        }
    }

};

