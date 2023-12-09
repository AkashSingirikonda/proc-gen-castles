#include "scene.h"

Scene::Scene()
{
    cameraData.pos = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
    cameraData.look = glm::vec4(0.0f);
    cameraData.up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

    cameraData.heightAngle = 49.5f;

    globalData.ka = 0.5f;
    globalData.kd = 0.5f;
    globalData.ks = 0.5f;
    globalData.kt = 0.0f;
}

Scene::~Scene()
{

}

