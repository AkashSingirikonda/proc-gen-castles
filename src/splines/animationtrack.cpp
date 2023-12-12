#include "animationtrack.h"


void AnimationTrack::append(TrackSegment* segment, float duration)
{
    segment->startTime = endTime;
    segment->duration = duration;
    segments.push_back(segment);
    endTime += duration;
}

void AnimationTrack::step(float time)
{
    if(param == nullptr)
    {
        return;
    }

    if(time > endTime)
    {
        return; // End of track
    }

    if(segments.size() <= 0)
    {
        return; // No segments have been set
    }

    TrackSegment* currentSegment = segments[segmentIndex];
    while(time - currentSegment->startTime > currentSegment->duration && segmentIndex < segments.size() - 1)
    {
        segmentIndex++;
        currentSegment = segments[segmentIndex];
    }

    float t = (time - currentSegment->startTime) / currentSegment->duration;

    if(t > 1)
    {
        t = 1;
    }

    if(currentSegment->easeFunction != nullptr)
    {
        t = currentSegment->easeFunction->get(t);
    }

    (*param) = currentSegment->get(t);
}
