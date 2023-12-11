#include "cameratrack.h"
#include <iostream>

CameraTrack::CameraTrack()
{

}

void CameraTrack::linkCamera(Camera* sceneCamera)
{
    camera = sceneCamera;
}

void CameraTrack::appendSegment(std::vector<CameraTrackSegment*>& segments, float* endTime, CameraTrackSegment* segment, float duration)
{
    segment->startTime = *endTime;
    segment->duration = duration;
    segments.push_back(segment);
    (*endTime) += duration;
}

glm::vec3 CameraTrack::getUpdatedParams(int* index, std::vector<CameraTrackSegment*>& segments)
{
    if(segments.size() <= 0)
    {
        return glm::vec3(0); // No segments have been set
    }

    CameraTrackSegment* currentSegment = segments[*index];
    while(currentTime - currentSegment->startTime > currentSegment->duration && *index < segments.size() - 1)
    {
        (*index)++;
        currentSegment = segments[*index];
    }

    float t = (currentTime - currentSegment->startTime) / currentSegment->duration;

    if(t > 1)
    {
        t = 1;
    }

    return currentSegment->get(t);
}

void CameraTrack::step(float deltaTime)
{
    if(isDone)
    {
        return; // Track finished
    }

    currentTime += deltaTime;

    if(currentTime > positionEndTime && currentTime > lookEndTime)
    {
        isDone = true;
        return; // End of track
    }



    camera->updatePos(getUpdatedParams(&positionSegmentIndex, positionSegments));
    camera->updateLook(getUpdatedParams(&lookSegmentIndex, lookSegments));
}

void CameraTrack::reset()
{
    currentTime = 0.0f;
    positionSegmentIndex = 0;
    lookSegmentIndex = 0;
    isDone = false;
}

void CameraTrack::stop()
{
    isDone = true;
}

void CameraTrack::AddDefaultSegments(CameraTrack& cameraTrack)
{
    LerpSegment* pos1 = new LerpSegment(glm::vec3(-1,0,1), glm::vec3(-1,3,15));
    ConstSegment* look1 = new ConstSegment(glm::vec3(-1,0,0));

    BezierSegment* pos2 = new BezierSegment(pos1, glm::vec3(10,3,15), glm::vec3(15,10,10), glm::vec3(15,10,-1));
    LerpSegment* look2 = new LerpSegment(look1, glm::vec3(5,0,5));

    cameraTrack.appendPositionSegment(pos1, 3);
    cameraTrack.appendLookSegment(look1, 2);

    cameraTrack.appendPositionSegment(pos2, 3);
    cameraTrack.appendLookSegment(look2, 8);
}
