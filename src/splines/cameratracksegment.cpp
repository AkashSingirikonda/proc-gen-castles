#include "cameratracksegment.h"


LerpSegment::LerpSegment(const CameraParams& start, const CameraParams& end)
{
    startParams = start;
    endParams = end;
}


void LerpSegment::get(float t, CameraParams& params)
{
    params.position = startParams.position * (1 - t) + endParams.position * t;
    params.look = startParams.look * (1 - t) + endParams.look * t;
}
