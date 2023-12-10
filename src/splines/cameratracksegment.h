#pragma once

#include "cameraparams.h"
#include "splines/spline.h"

class CameraTrackSegment
{
public:
    CameraTrackSegment(){};

    CameraTrackSegment(const CameraParams& start, const CameraParams& end);
    CameraTrackSegment(CameraTrackSegment* previous, const CameraParams& end);


    // Params are always computed assuming 0 <= t <= 1
    virtual void get(float t, CameraParams& params){params = CameraParams();};

public:
    // Track segments store their global start, end
    // These are managed by the parent track
    float startTime = 0;
    float duration = 1;

    CameraParams startParams;
    CameraParams endParams;

};

class LerpSegment : public CameraTrackSegment
{
public:
    LerpSegment(const CameraParams& start, const CameraParams& end) : CameraTrackSegment(start, end){};
    LerpSegment(CameraTrackSegment* previous, const CameraParams& end) : CameraTrackSegment(previous, end){};

    void get(float t, CameraParams& params) override;
};

class BezierSegment : public CameraTrackSegment
{
public:
    BezierSegment(const CameraParams& start, const CameraParams& p1, const CameraParams& p2, const CameraParams& end);
    BezierSegment(CameraTrackSegment* previous, const CameraParams& p1, const CameraParams& p2, const CameraParams& end);
    ~BezierSegment();

    void get(float t, CameraParams& params) override;

private:
    CubicSpline<glm::vec3>* positionSpline;
    CubicSpline<glm::vec3>* lookSpline;
};
