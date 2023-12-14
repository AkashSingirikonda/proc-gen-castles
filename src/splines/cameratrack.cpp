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

    TrackSegment* pos1 = new LerpSegment(glm::vec3(-1,1,10), glm::vec3(-1,1,2));
    TrackSegment* pos2 = new BezierSegment(pos1, glm::vec3(-1,1,-2), glm::vec3(-2,1,-1), glm::vec3(2,1,-1));

    TrackSegment* look1 = new ConstSegment(glm::vec3(-1, 1, -1));
    TrackSegment* look2 = new LerpSegment(look1, glm::vec3(3, 1, 3));
    TrackSegment* look3 = new ConstSegment(glm::vec3(3, 1, 3));

    cameraTrack.appendPositionSegment(pos1, 3);
    cameraTrack.appendLookSegment(look1, 2);

    cameraTrack.appendPositionSegment(pos2, 3);
    cameraTrack.appendLookSegment(look2, 2);
    cameraTrack.appendLookSegment(look3, 2);

    TrackSegment* pos3 = new BezierSegment(glm::vec3(2,1,-1), glm::vec3(5, 1, -1), glm::vec3(13, 15, -1), glm::vec3(20, 15, -1));
    TrackSegment* look4 = new LerpSegment(look3, glm::vec3(10, 1, 10));
    look4->SetEaseFunction(EaseType::EASE_OUT);

    cameraTrack.appendPositionSegment(pos3, 4);
    cameraTrack.appendLookSegment(look4, 4);

    TrackSegment* pos5 = new ConstSegment(glm::vec3(20, 15, -1));
    TrackSegment* look5 = new ConstSegment(glm::vec3(10, 1, 10));

    cameraTrack.appendPositionSegment(pos5, 1);
    cameraTrack.appendLookSegment(look5, 1);

    TrackSegment* pos6 = new BezierSegment(pos5, glm::vec3(17, 10, 2), glm::vec3(15, 1.5, 5), glm::vec3(15, 1.5, 10));
    TrackSegment* look6 = new LerpSegment(glm::vec3(10, 1, 10), glm::vec3(15, 1.5, 15));

    cameraTrack.appendPositionSegment(pos6, 4);
    cameraTrack.appendLookSegment(look6, 3);

    TrackSegment* pos7 = new BezierSegment(glm::vec3(15, 1.5, 10), glm::vec3(17, 1.5, 10), glm::vec3(10, 1.5, 17), glm::vec3(10, 1.5, 15));
    TrackSegment* look7 = new LerpSegment(glm::vec3(15, 1.5, 15), glm::vec3(10, 1.5, 10));

    cameraTrack.appendPositionSegment(pos7, 3);
    cameraTrack.appendLookSegment(look7, 2);

    TrackSegment* pos8 = new BezierSegment(glm::vec3(10, 1.5, 15), glm::vec3(10, 1.5, 13), glm::vec3(6, 2, 6), glm::vec3(5, 3, 5));
    TrackSegment* look8 = new LerpSegment(glm::vec3(10, 1.5, 10), glm::vec3(-15, 1, -15));
    look8->SetEaseFunction(EaseType::EASE_IN);

    cameraTrack.appendPositionSegment(pos8, 3);
    cameraTrack.appendLookSegment(look8, 6);

}
