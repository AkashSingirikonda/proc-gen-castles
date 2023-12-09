#include <stdexcept>
#include "camera.h"

#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"

Camera::Camera(SceneCameraData cameraData, float aspectRatio, float near, float far) {
    m_cameraData = cameraData;
    m_aspectRatio = aspectRatio;

    cameraPos = cameraData.pos;
    cameraLook = cameraData.look;
    cameraUp = cameraData.up;

    updateViewMatrix();

    updateNearFar(near, far);
}

void Camera::updateNearFar(float near, float far){
    glm::mat4 scaling = glm::mat4(0);
    scaling[2][2] = 1 / far;
    scaling[1][1] = scaling[2][2] / tan(m_cameraData.heightAngle / 2.0f);
    scaling[0][0] = scaling[1][1] / m_aspectRatio;
    scaling[3][3] = 1;
    float c = -near / far;

    glm::mat4 unhinging = glm::mat4(0);
    unhinging[0][0] = 1;
    unhinging[1][1] = 1;
    unhinging[2][2] = 1 / (1 + c);
    unhinging[3][2] = -c / (1 + c);
    unhinging[2][3] = -1;

    projMatrix = remapping * unhinging * scaling;
}

void Camera::updateViewMatrix(){
    cameraRight = glm::normalize(glm::cross(cameraLook - cameraPos, cameraUp));
    viewMatrix = glm::lookAt(cameraPos, cameraLook, cameraUp);
    invViewMatrix = glm::inverse(viewMatrix);
}
