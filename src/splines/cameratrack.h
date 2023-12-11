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

    void linkCamera(Camera* sceneCamera);

    void appendPositionSegment(CameraTrackSegment* segment, float duration){ appendSegment(positionSegments, &positionEndTime, segment, duration); };
    void appendLookSegment(CameraTrackSegment* segment, float duration){ appendSegment(lookSegments, &lookEndTime, segment, duration); };

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
    float endTime = 0.0f;

    void appendSegment(std::vector<CameraTrackSegment*>& segments, float* endTime, CameraTrackSegment* segment, float duration);

    float positionEndTime = 0.0f;
    int positionSegmentIndex = 0;
    std::vector<CameraTrackSegment*> positionSegments;

    float lookEndTime = 0.0f;
    int lookSegmentIndex = 0;
    std::vector<CameraTrackSegment*> lookSegments;

    glm::vec3 getUpdatedParams(int* index, std::vector<CameraTrackSegment*>& segments);

    Camera* camera;
};

