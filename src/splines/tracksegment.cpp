#include "tracksegment.h"


TrackSegment::TrackSegment(const glm::vec3 startPoint, const glm::vec3 endPoint)
{
    start = startPoint;
    end = endPoint;
}

TrackSegment::TrackSegment(TrackSegment* previous, const glm::vec3 endPoint)
{
    start = previous->end;
    end = endPoint;
}

void TrackSegment::SetEaseFunction(EaseType easeType)
{
    easeFunction = EaseFunctionGenerator::getEaseSpline(easeType);
}

BezierSegment::BezierSegment(const glm::vec3 startPoint, const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 endPoint)
{
    spline = new CubicSpline<glm::vec3>(startPoint, p1, p2, endPoint);
}

BezierSegment::BezierSegment(TrackSegment* previous, const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 endPoint)
{
    spline = new CubicSpline<glm::vec3>(previous->end, p1, p2, endPoint);
}

TangentSegment::TangentSegment(const glm::vec3 startPoint, const glm::vec3 t1, const glm::vec3 t2, const glm::vec3 endPoint)
{
    spline = new TangentSpline<glm::vec3>(startPoint, t1, t2, endPoint);
}

TangentSegment::TangentSegment(TrackSegment* previous, const glm::vec3 t1, const glm::vec3 t2, const glm::vec3 endPoint)
{
    spline = new TangentSpline<glm::vec3>(previous->end, t1, t2, endPoint);
}
