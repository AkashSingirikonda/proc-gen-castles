#pragma once

#include "cameraparams.h"
#include "splines/spline.h"

class TrackSegment
{
public:
    TrackSegment(){};

    TrackSegment(const glm::vec3 startPoint, const glm::vec3 endPoint);
    TrackSegment(TrackSegment* previous, const glm::vec3 endPoint);


    // Params are always computed assuming 0 <= t <= 1
    virtual glm::vec3 get(float t) = 0;

public:
    // Track segments store their global start, end
    // These are managed by the parent track
    float startTime = 0;
    float duration = 1;

    glm::vec3 start;
    glm::vec3 end;

};

class ConstSegment : public TrackSegment
{
public:
    ConstSegment(const glm::vec3 value) : TrackSegment(value, value) {};
    ConstSegment(TrackSegment* previous) : TrackSegment(previous, previous->end) {};

    glm::vec3 get(float t) override { return end; };
};

class LerpSegment : public TrackSegment
{
public:
    LerpSegment(const glm::vec3 startPoint, const glm::vec3 endPoint) : TrackSegment(startPoint, endPoint) {};
    LerpSegment(TrackSegment* previous, const glm::vec3 endPoint) : TrackSegment(previous->end, endPoint) {};

    glm::vec3 get(float t) override { return (1-t) * start + t * end; };
};

class BezierSegment : public TrackSegment
{
public:
    BezierSegment(const glm::vec3 startPoint, const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 endPoint);
    BezierSegment(TrackSegment* previous, const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 endPoint);
    ~BezierSegment(){ delete spline; };

    glm::vec3 get(float t) override { return spline->get(t); };

private:
    CubicSpline<glm::vec3>* spline;
};
