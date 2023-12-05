
template <class T>
class Spline
{
public:
    Spline(T startData, T endData){start = startData; end = endData;};

    virtual T get(float time) = 0;

protected:
    T start;
    T end;
};

template <class T>
class LinearSpline : public Spline<T>
{
    LinearSpline(T startData, T endData): Spline<T>(startData, endData){};

    T get(float time) override;
};

/*
 * TODO
 *
 * Cubic Spline
 * Cosine Spline
 *
 *
 * degree 1 spline (velocity)
 * degree 2 spline (velocity + accel)
 *
 *
 * bezier spline (2 more data points)
 *
 * premade cubic-bezier
 *  - ease
 *  - ease-in
 *  - ease-out
 *  - ease-in-out
 *
 *  https://cubic-bezier.com/#0,1,1,0
 *
 *
 */
