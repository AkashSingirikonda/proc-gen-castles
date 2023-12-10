#include "cameratrack.h"
#include <iostream>

CameraTrack::CameraTrack()
{

}

void CameraTrack::linkCamera(Camera* sceneCamera)
{
    camera = sceneCamera;
}

void CameraTrack::AppendSegment(CameraTrackSegment* segment, float duration)
{
    segment->startTime = endTime;
    segment->duration = duration;
    segments.push_back(segment);
    endTime += duration;
}

void CameraTrack::step(float deltaTime)
{
    currentTime += deltaTime;

    if(segments.size() <= 0)
    {
        return; // No segments have been set
    }

    if(currentTime > endTime)
    {
        return; // End of track
    }

    CameraTrackSegment* currentSegment = segments[currentSegmentIndex];
    while(currentTime - currentSegment->startTime > currentSegment->duration && currentSegmentIndex < segments.size() - 1)
    {
        currentSegmentIndex++;
        currentSegment = segments[currentSegmentIndex];
    }

    float t = (currentTime - currentSegment->startTime) / currentSegment->duration;

    CameraParams cameraParams;
    currentSegment->get(t, cameraParams);

    camera->updatePos(cameraParams.position);
    camera->updateLook(cameraParams.look);
}


void CameraTrack::AddDefaultSegments(CameraTrack& cameraTrack)
{
    LerpSegment* segment = new LerpSegment({glm::vec3(-1,0,1), glm::vec3(-1,0,0)}, {glm::vec3(-1,3,15), glm::vec3(-1,0,0)});
    BezierSegment* segment2 = new BezierSegment(segment, {glm::vec3(10,3,15), glm::vec3(0)}, {glm::vec3(15,10,10), glm::vec3(0)}, {glm::vec3(15,10,-1), glm::vec3(5,0,5)});

    cameraTrack.AppendSegment(segment, 5);
    cameraTrack.AppendSegment(segment2, 5);
}
