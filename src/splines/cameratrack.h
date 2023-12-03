#include "glm/glm.hpp"

struct CameraParams {
    glm::vec3 position;
    glm::vec3 look;
};


class CameraTrack
{
public:
    CameraTrack();

    void AddSegment(){};

    void get(float t, CameraParams& params){};
};

