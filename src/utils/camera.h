#pragma once

#include <glm/glm.hpp>
#include "utils/scenedata.h"

class Camera {
public:

    Camera(){};
    Camera(SceneCameraData cameraData, float aspectRatio, float near, float far);

    void updateNearFar(float near, float far);
    void update();

public:
    SceneCameraData m_cameraData;
    float m_aspectRatio;

    glm::mat4 viewMatrix;
    glm::mat4 invViewMatrix;

    glm::vec3 cameraPos;
    glm::vec3 cameraLook;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;

    glm::mat4 projMatrix;

    void updateViewMatrix();

private:
    glm::mat4 remapping = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -2, 0, 0, 0, -1, 1);

};
