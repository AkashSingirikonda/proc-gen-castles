#include "cameratracksegment.h"


LerpSegment::LerpSegment(const CameraParams& start, const CameraParams& end)
{
    startParams = start;
    endParams = end;
}


void LerpSegment::get(float t, CameraParams& params)
{
    params.position = startParams.position * t + endParams.position * (1 - t);
    params.look = startParams.look * t + endParams.look * (1 - t);
}
