#include "cameratrack.h"
#include <iostream>

CameraTrack::CameraTrack()
{

}

void CameraTrack::linkCamera(Camera* sceneCamera)
{
    camera = sceneCamera;
    positionTrack.linkParam(camera->getPosPointer());
    lookTrack.linkParam(camera->getLookPointer());
}

void CameraTrack::step(float deltaTime)
{
    if(isDone)
    {
        return;
    }

    currentTime += deltaTime;

    if(positionTrack.isFinished(currentTime) && lookTrack.isFinished(currentTime))
    {
        isDone = true;
        return;
    }

    positionTrack.step(currentTime);
    lookTrack.step(currentTime);
    camera->markDirty();
}

void CameraTrack::reset()
{
    currentTime = 0.0f;
    positionTrack.reset();
    lookTrack.reset();
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
