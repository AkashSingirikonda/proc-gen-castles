#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "cameratracksegment.h"

#include "utils/camera.h"

class CameraTrack
{
public:
    CameraTrack();

    void AppendSegment(CameraTrackSegment* segment, float duration);

    void linkCamera(Camera* sceneCamera);

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
    int currentSegmentIndex = 0;

    float endTime = 0.0f;
    std::vector<CameraTrackSegment*> segments;

    Camera* camera;
};

