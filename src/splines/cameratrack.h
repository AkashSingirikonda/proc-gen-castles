#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "cameratracksegment.h"
#include "cameraparams.h"

#include "utils/camera.h"

class CameraTrack
{
public:
    CameraTrack(Camera* sceneCamera);
    ~CameraTrack();

    void AppendSegment(CameraTrackSegment* segment, float duration);

    void get(float t, CameraParams& params){};

private:
    float endTime = 0.0f;
    std::vector<CameraTrackSegment*> segments;

    Camera* camera;
};

