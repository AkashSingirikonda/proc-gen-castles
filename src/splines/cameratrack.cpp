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
    {
        CameraParams p1 = {glm::vec3(10,5,0), glm::vec3(0)};
        CameraParams p2 = {glm::vec3(0,5,10), glm::vec3(0)};
        LerpSegment* segment = new LerpSegment(p1, p2);
        cameraTrack.AppendSegment(segment, 3);
    }

    {
        CameraParams p1 = {glm::vec3(0,5,10), glm::vec3(0, 0, 0)};
        CameraParams p2 = {glm::vec3(10,5,10), glm::vec3(5, 0, 5)};
        LerpSegment* segment = new LerpSegment(p1, p2);
        cameraTrack.AppendSegment(segment, 3);
    }

    {
        CameraParams p1 = {glm::vec3(10,5,10), glm::vec3(5, 0, 5)};
        CameraParams p2 = {glm::vec3(-5,20,20), glm::vec3(5, 0, 5)};
        LerpSegment* segment = new LerpSegment(p1, p2);
        cameraTrack.AppendSegment(segment, 5);
    }
}
