#include <stdexcept>
#include "camera.h"

#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"

Camera::Camera(SceneCameraData cameraData, float cameraAspectRatio, float cameraNear, float cameraFar)
{
    aspectRatio = cameraAspectRatio;
    heightAngle = cameraData.heightAngle;
    nearPlane = cameraNear;
    farPlane = cameraFar;

    pos = cameraData.pos;
    look = cameraData.look;
    up = cameraData.up;

    updateViewMatrix();

    updateScalingMatrix();
    updateUnhingingMatrix();
    updateProjMatrix();
}

void Camera::updateHeightAngle(float newHeightAngle)
{
    heightAngle = newHeightAngle;
    updateScalingMatrix();
    updateProjMatrix();
}

void Camera::updateNearFar(float newNearDistance, float newFarDistance)
{
    nearPlane = newNearDistance;
    farPlane = newFarDistance;
    updateScalingMatrix();
    updateUnhingingMatrix();
    updateProjMatrix();
}

void Camera::updatePos(glm::vec3 cameraPos)
{
    pos = cameraPos;
    updateViewMatrix();
}

void Camera::updateLook(glm::vec3 cameraLook)
{
    look = cameraLook;
    updateViewMatrix();
}
void Camera::updateUp(glm::vec3 cameraUp)
{
    up = cameraUp;
    updateViewMatrix();
}

void Camera::updatePosLook(glm::vec3 cameraPos, glm::vec3 cameraLook)
{
    pos = cameraPos;
    look = cameraLook;
    updateViewMatrix();
}

void Camera::updatePosLookUp(glm::vec3 cameraPos, glm::vec3 cameraLook, glm::vec3 cameraUp)
{
    pos = cameraPos;
    look = cameraLook;
    up = cameraUp;
    updateViewMatrix();
}

void Camera::updateViewMatrix()
{
    right = glm::normalize(glm::cross(look - pos, up));
    viewMatrix = glm::lookAt(pos, look, up);
    invViewMatrix = glm::inverse(viewMatrix);
}

void Camera::updateScalingMatrix()
{
    scaling = glm::mat4(0);
    scaling[2][2] = 1 / farPlane;
    scaling[1][1] = scaling[2][2] / tan(heightAngle / 2.0f);
    scaling[0][0] = scaling[1][1] / aspectRatio;
    scaling[3][3] = 1;
}

void Camera::updateUnhingingMatrix()
{
    float c = -nearPlane / farPlane;

    unhinging = glm::mat4(0);
    unhinging[0][0] = 1;
    unhinging[1][1] = 1;
    unhinging[2][2] = 1 / (1 + c);
    unhinging[3][2] = -c / (1 + c);
    unhinging[2][3] = -1;
}

void Camera::updateProjMatrix()
{
    projMatrix = remapping * unhinging * scaling;
}
