#pragma once

#include "spline.h"

enum EaseType {
    EASE,
    EASE_IN,
    EASE_OUT,
    EASE_IN_OUT
};


class SceneLoader
{
public:
    static EaseSpline getEaseSpline(EaseType easeType)
    {
        switch(easeType)
        {
        case EaseType::EASE:
            return EaseSpline(0.25f, 0.1f, 0.25f, 1.0f);
        case EaseType::EASE_IN:
            return EaseSpline(0.42f, 0.0f, 1.0f, 1.0f);
        case EaseType::EASE_OUT:
            return EaseSpline(0.0f, 0.0f, 0.58f, 1.0f);
        case EaseType::EASE_IN_OUT:
            return EaseSpline(0.42f, 0.0f, 0.58f, 1.0f);
        default:
            return EaseSpline(0,0,1,1);
        }
    }
};
