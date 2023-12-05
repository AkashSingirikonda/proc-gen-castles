#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "cameratracksegment.h"
#include "cameraparams.h"

class CameraTrack
{
public:
    CameraTrack();
    ~CameraTrack();

    void AppendSegment(CameraTrackSegment* segment, float duration){};

    void get(float t, CameraParams& params){};

private:
    std::vector<CameraTrackSegment*> segments;
};

