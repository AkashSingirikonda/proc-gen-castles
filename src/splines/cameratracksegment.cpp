#include "cameratracksegment.h"


CameraTrackSegment::CameraTrackSegment(const CameraParams& start, const CameraParams& end)
{
    startParams = start;
    endParams = end;
}

CameraTrackSegment::CameraTrackSegment(CameraTrackSegment* previous, const CameraParams& end)
{
    startParams = previous->startParams;
    endParams = end;
}

void LerpSegment::get(float t, CameraParams& params)
{
    params.position = startParams.position * (1 - t) + endParams.position * t;
    params.look = startParams.look * (1 - t) + endParams.look * t;
}

BezierSegment::BezierSegment(const CameraParams& start, const CameraParams& p1, const CameraParams& p2, const CameraParams& end)
{
    positionSpline = new CubicSpline<glm::vec3>(start.position, p1.position, p2.position, end.position);
    lookSpline = new CubicSpline<glm::vec3>(start.look, p1.look, p2.look, end.look);
}

BezierSegment::BezierSegment(CameraTrackSegment* previous, const CameraParams& p1, const CameraParams& p2, const CameraParams& end)
{
    positionSpline = new CubicSpline<glm::vec3>(previous->endParams.position, p1.position, p2.position, end.position);
    lookSpline = new CubicSpline<glm::vec3>(previous->endParams.look, p1.look, p2.look, end.look);
}

BezierSegment::~BezierSegment()
{
    delete positionSpline;
    delete lookSpline;
}

void BezierSegment::get(float t, CameraParams& params)
{
    params.position = positionSpline->get(t);
    params.look = lookSpline->get(t);
}
