#include "spline.h"

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

EaseSpline::EaseSpline(float x1, float y1, float x2, float y2)
{
    for(float t = 0.0f; t <= 1.0f; t += SEGMENT_SIZE)
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
        int middle = 0.5f * (right + left);
        if(data[middle] > t)
        {
            right = middle;
        }
        else
        {
            left = middle;
        }
    }
    float t1 = SEGMENT_SIZE * left;
    float t2 = SEGMENT_SIZE * right;
    t = (t2 - t1) * (t - data[left]) / (data[right] - data[left]);
    return 3 * t * (1-t) * (1-t) * p1 + 3 * t * t * (1-t) * p2 + t * t * t;
}


template class LinearSpline<float>;
template class LinearSpline<glm::vec3>;
template class LinearSpline<glm::vec4>;

template class CubicSpline<float>;
template class CubicSpline<glm::vec3>;
template class CubicSpline<glm::vec4>;
