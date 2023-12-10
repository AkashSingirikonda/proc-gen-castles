#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

template <class T>
class Spline
{
public:
    Spline(){};

    virtual T get(float time) = 0;

};

template <class T>
class LinearSpline : public Spline<T>
{
public:
    LinearSpline(T startData, T endData);

    T get(float time) override;
private:
    T start;
    T end;
};

template <class T>
class CubicSpline : public Spline<T>
{
public:
    CubicSpline(T startData, T p1, T p2, T endData);

    T get(float time) override;
private:
    T start;
    T end;
    T p1;
    T p2;
};


class EaseSpline : public Spline<float>
{
public:
    EaseSpline(float x1, float y1, float x2, float y2);

    float get(float time) override;
private:
    /*
     * Solving cubic equation to compute exactly is non trivial.
     * Instead we precompute values and then interpolate between them
     */
    std::vector<float> data;
    float SEGMENT_SIZE = 0.05f;

    float p1;
    float p2;
};
