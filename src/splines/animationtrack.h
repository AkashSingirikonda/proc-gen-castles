#pragma once

#include "tracksegment.h"

class AnimationTrack
{
public:
    AnimationTrack(){};

    void linkParam(glm::vec3* updateParam){ param = updateParam; };

    void append(TrackSegment* segment, float duration);

    void step(float time);
    void reset(){ segmentIndex = 0; };

    const bool isFinished(float time) const { return time > endTime; };

private:
    glm::vec3* param = nullptr;

    float endTime = 0.0f;
    int segmentIndex = 0;
    std::vector<TrackSegment*> segments;


};
