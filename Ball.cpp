#include "Ball.hpp"

namespace RoboDodge
{
    Ball::Ball(float iradius, float ix, float iy, float ixspeed, float iyspeed)
    {
        radius = iradius;
        x = ix;
        y = iy;
        xspeed = ixspeed;
        yspeed = iyspeed;
    }

    void Ball::UpdatePosition(float timeElapsed)
    {
        x += xspeed * timeElapsed;
        y += yspeed * timeElapsed;
    }

    float Ball::GetX()
    {
        return x;
    }

    float Ball::GetY()
    {
        return y;
    }
}
