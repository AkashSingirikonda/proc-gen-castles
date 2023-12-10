#include "cameratrack.h"

CameraTrack::CameraTrack(Camera* sceneCamera)
{
    camera = sceneCamera;
}


void CameraTrack::AppendSegment(CameraTrackSegment* segment, float duration)
{
    segment->setStartTime(endTime);
    segment->setDuration(duration);
    segments.push_back(segment);
}
