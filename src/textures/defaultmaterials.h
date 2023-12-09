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
            material.cSpecular = SceneColor(1.0f, 1.5f, 1.0f, 1.0f);
            break;
        case TextureType::TEXTURE_STONE:
            material.cAmbient = SceneColor(0.6f, 0.6f, 0.6f, 1.0f);
            material.cDiffuse = SceneColor(0.5f, 0.5f, 0.5f, 1.0f);
            material.cSpecular = SceneColor(1.0f, 1.5f, 1.0f, 1.0f);
            break;
        case TextureType::TEXTURE_ROOF:
            material.cAmbient = SceneColor(0.9f, 0.3f, 0.0f, 1.0f);
            material.cDiffuse = SceneColor(0.5f, 0.5f, 0.5f, 1.0f);
            material.cSpecular = SceneColor(1.0f, 1.5f, 1.0f, 1.0f);
            break;
        default:
            break;
        }

        return material;
    };
}
