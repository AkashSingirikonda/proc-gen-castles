#pragma once

#include <string>
#include <glm/glm.hpp>
#include "scene/scenedata.h"
#include "textures/texturetypes.h"

// Struct which contains data for texture mapping files
struct SceneFileMap {
    SceneFileMap() : isUsed(false) {}

    bool isUsed;
    std::string filename;

    float repeatU;
    float repeatV;

    void clear()
    {
        isUsed = false;
        repeatU = 0.0f;
        repeatV = 0.0f;
        filename = std::string();
    }
};

// Struct which contains data for a material (e.g. one which might be assigned to an object)
struct SceneMaterial {
    SceneColor cAmbient;  // Ambient term
    SceneColor cDiffuse;  // Diffuse term
    SceneColor cSpecular; // Specular term
    float shininess;      // Specular exponent

    SceneColor cReflective; // Used to weight contribution of reflected ray lighting (via multiplication)

    SceneColor cTransparent; // Transparency;        used for extra credit (refraction)
    float ior;               // Index of refraction; used for extra credit (refraction)

    SceneFileMap textureMap; // Used for texture mapping
    SceneFileMap normalMap;
    TextureType type;
    float blend;             // Used for texture mapping

    SceneColor cEmissive; // Not used
    SceneFileMap bumpMap; // Not used

    void clear()
    {
        cAmbient = glm::vec4(0);
        cDiffuse = glm::vec4(0);
        cSpecular = glm::vec4(0);
        shininess = 0;

        cReflective = glm::vec4(0);

        cTransparent = glm::vec4(0);
        ior = 0;

        textureMap.clear();
        blend = 0;

        cEmissive = glm::vec4(0);
        bumpMap.clear();
    }
};
