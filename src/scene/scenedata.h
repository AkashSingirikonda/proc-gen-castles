#pragma once

#include <glm/glm.hpp>

#include "textures/texturedata.h"

// Struct which contains the global color coefficients of a scene.
// These are multiplied with the object-specific materials in the lighting equation.
struct SceneGlobalData {
    float ka; // Ambient term
    float kd; // Diffuse term
    float ks; // Specular term
    float kt; // Transparency; used for extra credit (refraction)
};


// Enum of the types of virtual lights that might be in the scene
enum class LightType {
    LIGHT_POINT,
    LIGHT_DIRECTIONAL,
    LIGHT_SPOT,
};

// Type which can be used to store an RGBA color in floats [0,1]
using SceneColor = glm::vec4;

struct SceneLightData {
    int id;
    LightType type;

    SceneColor color;
    glm::vec3 function; // Attenuation function

    glm::vec4 pos; // Position with CTM applied (Not applicable to directional lights)
    glm::vec4 dir; // Direction with CTM applied (Not applicable to point lights)

    float penumbra; // Only applicable to spot lights, in RADIANS
    float angle;    // Only applicable to spot lights, in RADIANS

    float width, height; // No longer supported (area lights)
};

// Struct which contains data for the camera of a scene
struct SceneCameraData {
    glm::vec4 pos;
    glm::vec4 look;
    glm::vec4 up;

    float heightAngle; // The height angle of the camera in RADIANS

    float aperture;    // Only applicable for depth of field
    float focalLength; // Only applicable for depth of field
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
