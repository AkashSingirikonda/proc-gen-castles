#pragma once

#include <glm/glm.hpp>


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
    LightType type;
    SceneColor color = SceneColor(1.0, 1.0, 1.0, 0.0);
    glm::vec3 function = glm::vec3(0.8f, 0.05f, 0.0f); // Attenuation function
    glm::vec4 direction;

    float penumbra = 0.35f;
    float angle = 0.52f;
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
