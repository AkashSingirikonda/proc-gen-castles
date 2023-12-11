#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "tracksegment.h"
#include "animationtrack.h"
#include "utils/camera.h"

class CameraTrack
{
public:
    CameraTrack();
    void linkCamera(Camera* sceneCamera);

    void appendPositionSegment(TrackSegment* segment, float duration){ positionTrack.append(segment, duration); };
    void appendLookSegment(TrackSegment* segment, float duration){ lookTrack.append(segment, duration); };

    void step(float deltaTime);
    void reset();
    void stop();

    const bool isTrackFinished() const {return isDone;};

private:
    bool isDone = false;

public:
    static void AddDefaultSegments(CameraTrack& cameraTrack);

private:
    float currentTime = 0.0f;

    AnimationTrack positionTrack;
    AnimationTrack lookTrack;

    Camera* camera;
};

