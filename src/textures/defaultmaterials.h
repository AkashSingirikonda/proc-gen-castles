#pragma once

#include "texturetypes.h"
#include "texturedata.h"

class DefaultMaterials
{
public:
    static SceneMaterial getDefaultMaterial(TextureType type)
    {
        SceneMaterial material = SceneMaterial();

        switch(type)
        {
        case TextureType::TEXTURE_GRASS:
            material.cAmbient = SceneColor(0.0f, 0.5f, 0.0f, 1.0f);
            material.cDiffuse = SceneColor(0.5f, 0.5f, 0.5f, 1.0f);
            material.cSpecular = SceneColor(1.0f, 1.0f, 1.0f, 1.0f);
            material.shininess = 15;
            material.normalMap = SceneFileMap();
            material.normalMap.filename = ":/resources/images/grass.png";
            material.normalMap.isUsed = 1;
            break;
        case TextureType::TEXTURE_STONE:
            material.cAmbient = SceneColor(0.6f, 0.6f, 0.6f, 1.0f);
            material.cDiffuse = SceneColor(0.5f, 0.5f, 0.5f, 1.0f);
            material.cSpecular = SceneColor(1.0f, 1.0f, 1.0f, 1.0f);
            material.shininess = 15;
            // adding mapping values
            material.normalMap = SceneFileMap();
            material.normalMap.filename = ":/resources/images/Wall_Stone_Normal_Map.png";
            material.normalMap.isUsed = 1;
            break;
        case TextureType::TEXTURE_ROOF:
            material.cAmbient = SceneColor(0.9f, 0.3f, 0.0f, 1.0f);
            material.cDiffuse = SceneColor(0.5f, 0.5f, 0.5f, 1.0f);
            material.cSpecular = SceneColor(1.0f, 1.0f, 1.0f, 1.0f);
            material.shininess = 15;
            material.normalMap = SceneFileMap();
            material.normalMap.filename = ":/resources/images/Roof_Tile_Map.png";
            material.normalMap.isUsed = 1;
            break;
        default:
            material.cAmbient = SceneColor(1.0f, 1.0f, 1.0f, 1.0f);
            material.cDiffuse = SceneColor(0.5f, 0.5f, 0.5f, 1.0f);
            material.cSpecular = SceneColor(1.0f, 1.0f, 1.0f, 1.0f);
            material.shininess = 15;
            break;
        }

        return material;
    };
};
