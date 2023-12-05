#include "spline.h"

template <class T>
T LinearSpline<T>::get(float t)
{
    return this->start * (1-t) + this->end * t;
}
