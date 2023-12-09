#pragma once

#include <string>

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
