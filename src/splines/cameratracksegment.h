
#include "cameratrack.h"

class CameraTrackSegment
{
public:
    CameraTrackSegment();

    void get(float t, CameraParams& params){};

    void setStartTime(float time) {startTime = time;}
    void setEndTime(float time) {endTime = time;}

    float startTime = 0;
    float endTime = 1;

};
