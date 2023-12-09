#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "scene/scene.h"
#include "scene/sceneprimitive.h"
#include "renderobject.h"

class SceneLoader
{
public:
    static void GetRenderObjectsForScene(Scene& scene, std::map<PrimitiveType, ScenePrimitive*>& primitiveTypes,
                                         std::map<TextureType, SceneMaterial>& materialTypes,
                                         std::vector<RenderObject*>& renderObjects, std::vector<RenderLight*>& renderLights)
    {
        if(scene.root == nullptr)
        {
            return;
        }
        buildSceneRecursive(scene.root, glm::mat4(1), primitiveTypes, materialTypes, renderObjects, renderLights);
    }


    static void buildSceneRecursive(SceneNode* node, glm::mat4 ctm, std::map<PrimitiveType, ScenePrimitive*>& primitiveTypes,
                                    std::map<TextureType, SceneMaterial>& materialTypes,
                                    std::vector<RenderObject*>& renderObjects, std::vector<RenderLight*>& renderLights)
    {
        ctm = ctm * node->transform;

        for(SceneObject* sceneObject : node->objects)
        {
            PrimitiveType primitiveType = sceneObject->primitive;
            TextureType textureType = sceneObject->texture;

            if(!primitiveTypes.contains(primitiveType))
            {
                std::cout << "Encountered unknown primitive on load" << std::endl;
            }

            if(!materialTypes.contains(textureType))
            {
                std::cout << "Encountered unknown material on load" << std::endl;
            }

            ScenePrimitive* primitive = primitiveTypes.find(primitiveType)->second;
            SceneMaterial* material = &materialTypes.find(textureType)->second;

            RenderObject* renderObject = new RenderObject(ctm * sceneObject->transform, primitive, material);
            renderObjects.push_back(renderObject);
        }

        for(SceneLight* sceneLight : node->lights){
            RenderLight* renderLight = new RenderLight(ctm * sceneLight->transform, sceneLight->lightData);
            renderLights.push_back(renderLight);
        }

        if(node->children.size() <= 0)
        {
            return;
        }

        for(SceneNode* child : node->children)
        {
            buildSceneRecursive(child, ctm, primitiveTypes, materialTypes, renderObjects, renderLights);
        }
    }
};

