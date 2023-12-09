#pragma once

#include <glm/glm.hpp>
#include "scene/scenedata.h"

class Camera {
public:

    Camera(){};
    Camera(SceneCameraData cameraData, float cameraAspectRatio, float cameraNear, float cameraFar);


    void updateHeightAngle(float newHeightAngle);
    void updateAspectRatio(float newAspectRatio);
    void updateNearFar(float newNearDistance, float newFarDistance);

    void updatePos(glm::vec3 pos);
    void updateLook(glm::vec3 look);
    void updateUp(glm::vec3 up);
    void updatePosLook(glm::vec3 pos, glm::vec3 look);
    void updatePosLookUp(glm::vec3 pos, glm::vec3 look, glm::vec3 up);

    void rotateRoll(float angle);
    void rotatePitch(float angle);
    void rotateYaw(float angle);

    void move(float forwardStep, float rightStep, float upStep);


    glm::vec3& getCameraPos(){ return pos; };
    glm::mat4& getViewMatrix(){ return viewMatrix; };
    glm::mat4& getInvViewMatrix(){ return invViewMatrix; };
    glm::mat4& getProjMatrix(){ return projMatrix; };

private:
    float heightAngle;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    glm::vec3 pos;
    glm::vec3 look;
    glm::vec3 up;
    glm::vec3 right;

    glm::mat4 viewMatrix;
    glm::mat4 invViewMatrix;

    glm::mat4 scaling;
    glm::mat4 unhinging;
    glm::mat4 remapping = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -2, 0, 0, 0, -1, 1);

    glm::mat4 projMatrix;

private:
    void updateViewMatrix();

    void updateScalingMatrix();
    void updateUnhingingMatrix();

    void updateProjMatrix();
};
