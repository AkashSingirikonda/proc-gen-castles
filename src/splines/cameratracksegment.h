#pragma once

#include "cameraparams.h"

class CameraTrackSegment
{
public:
    CameraTrackSegment(){};

    // Params are always computed assuming 0 <= t <= 1
    virtual void get(float t, CameraParams& params){params = CameraParams();};

public:
    // Track segments store their global start, end
    // These are managed by the parent track
    float startTime = 0;
    float duration = 1;

};


class LerpSegment : public CameraTrackSegment
{
public:
    LerpSegment(const CameraParams& start, const CameraParams& end);

    void get(float t, CameraParams& params) override;

private:
    CameraParams startParams;
    CameraParams endParams;
};
