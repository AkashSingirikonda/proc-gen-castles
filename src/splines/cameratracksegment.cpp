#include "cameratracksegment.h"


CameraTrackSegment::CameraTrackSegment(const glm::vec3 startPoint, const glm::vec3 endPoint)
{
    start = startPoint;
    end = endPoint;
}

CameraTrackSegment::CameraTrackSegment(CameraTrackSegment* previous, const glm::vec3 endPoint)
{
    start = previous->end;
    end = endPoint;
}

BezierSegment::BezierSegment(const glm::vec3 startPoint, const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 endPoint)
{
    spline = new CubicSpline<glm::vec3>(startPoint, p1, p2, endPoint);
}

BezierSegment::BezierSegment(CameraTrackSegment* previous, const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 endPoint)
{
    spline = new CubicSpline<glm::vec3>(previous->end, p1, p2, endPoint);
}
