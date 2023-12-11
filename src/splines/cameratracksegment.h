#pragma once

#include "cameraparams.h"
#include "splines/spline.h"

class CameraTrackSegment
{
public:
    CameraTrackSegment(){};

    CameraTrackSegment(const glm::vec3 startPoint, const glm::vec3 endPoint);
    CameraTrackSegment(CameraTrackSegment* previous, const glm::vec3 endPoint);


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

class ConstSegment : public CameraTrackSegment
{
public:
    ConstSegment(const glm::vec3 value) : CameraTrackSegment(value, value) {};
    ConstSegment(CameraTrackSegment* previous) : CameraTrackSegment(previous, previous->end) {};

    glm::vec3 get(float t) override { return end; };
};

class LerpSegment : public CameraTrackSegment
{
public:
    LerpSegment(const glm::vec3 startPoint, const glm::vec3 endPoint) : CameraTrackSegment(startPoint, endPoint) {};
    LerpSegment(CameraTrackSegment* previous, const glm::vec3 endPoint) : CameraTrackSegment(previous->end, endPoint) {};

    glm::vec3 get(float t) override { return (1-t) * start + t * end; };
};

class BezierSegment : public CameraTrackSegment
{
public:
    BezierSegment(const glm::vec3 startPoint, const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 endPoint);
    BezierSegment(CameraTrackSegment* previous, const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 endPoint);
    ~BezierSegment(){ delete spline; };

    glm::vec3 get(float t) override { return spline->get(t); };

private:
    CubicSpline<glm::vec3>* spline;
};
