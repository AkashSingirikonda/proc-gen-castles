#include "spline.h"
#include <iostream>

template <class T>
LinearSpline<T>::LinearSpline(T startData, T endData)
{
    start = startData;
    end = startData;
}

template <class T>
T LinearSpline<T>::get(float t)
{
    return (1-t) * start + t * end;
}

template <class T>
CubicSpline<T>::CubicSpline(T startData, T p1Data, T p2Data, T endData)
{
    start = startData;
    p1 = p1Data;
    p2 = p2Data;
    end = endData;
}

template <class T>
T CubicSpline<T>::get(float t)
{
    return (1.0f-t) * (1-t) * (1-t) * start
           + 3 * t * (1-t) * (1-t) * p1
           + 3 * t * t * (1-t) * p2
           + t * t * t * end;
}

template <class T>
TangentSpline<T>::TangentSpline(T startData, T t1Data, T t2Data, T endData)
{
    start = startData;
    t2 = t2Data;
    end = endData;
    a = 2.0f * startData + t1Data + t2Data - 2.0f * endData;
    b = 3.0f * endData - 2.0f * t2Data - t1Data - 3.0f * startData;
}

template <class T>
T TangentSpline<T>::get(float t)
{
    return t * t * t * a
           + t * t * b
           + t * t2
           + start;
}

EaseSpline::EaseSpline(float x1, float y1, float x2, float y2)
{
    for(float t = 0.0f; t < 1.0f; t += SEGMENT_SIZE)
    {
        data.push_back(3 * t * (1-t) * (1-t) * x1 + 3 * t * t * (1-t) * x2 + t * t * t);
    }
    p1 = y1;
    p2 = y2;
}

float EaseSpline::get(float t)
{
    int left = 0;
    int right = data.size() - 1;
    while(right - left > 1)
    {
        int middle = round(0.5f * (right + left));
        if(t < data[middle])
        {
            right = middle;
        }
        else
        {
            left = middle;
        }
    }
    t = SEGMENT_SIZE * (t - data[left]) / (data[right] - data[left]) + data[left];
    return 3 * t * (1-t) * (1-t) * p1 + 3 * t * t * (1-t) * p2 + t * t * t;
}


template class LinearSpline<float>;
template class LinearSpline<glm::vec3>;
template class LinearSpline<glm::vec4>;

template class CubicSpline<float>;
template class CubicSpline<glm::vec3>;
template class CubicSpline<glm::vec4>;

template class TangentSpline<float>;
template class TangentSpline<glm::vec3>;
template class TangentSpline<glm::vec4>;
