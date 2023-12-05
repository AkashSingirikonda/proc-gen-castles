#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

struct CameraParams {
    glm::vec3 position;
    glm::vec3 look;

    CameraParams(){
        position = glm::vec3(0.0f);
        look = glm::vec3(0.0f);
    }
};
