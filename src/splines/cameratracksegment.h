#include "cameraparams.h"




class CameraTrackSegment
{
public:
    CameraTrackSegment(){};

    // Params are always computed assuming 0 <= t <= 1
    virtual void get(float t, CameraParams& params){params = CameraParams();};


    // Track segments store their global start, end
    // These are managed by the parent track
    void setStartTime(float time){startTime = time;}
    void setDuration(float time) {duration = time;}

private:
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


// Single spline for each camera parameter
class JoinedParameterSegment : public CameraTrackSegment
{
public:
    JoinedParameterSegment();
};


// Separate spline for each camera paramter
class SplitParameterSegment : public CameraTrackSegment
{
public:
    SplitParameterSegment();
};
