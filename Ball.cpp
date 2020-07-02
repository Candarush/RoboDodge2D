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

    void Ball::UpdatePosition(float timeElapsed, Surface ground)
    {
        Bounce(ground);
        
        x += xspeed * timeElapsed;
        y += yspeed * timeElapsed;
        
    }

    void Ball::Bounce(Surface ground)
    {
        if (x + radius > ground.GetWidth() && xspeed > 0)
        {
            xspeed = -xspeed;
        }
        
        if (x - radius < 0 && xspeed < 0)
        {
            xspeed = -xspeed;
        }
        
        if (y + radius > ground.GetHeight() && yspeed > 0)
        {
            yspeed = -yspeed;
        }
        
        if (y - radius < 0 && yspeed < 0)
        {
            yspeed = -yspeed;
        }
    }

    float Ball::GetX()
    {
        return x;
    }

    float Ball::GetY()
    {
        return y;
    }
    
    float Ball::GetSpeedX()
    {
        return xspeed;
    }

    float Ball::GetSpeedY()
    {
        return yspeed;
    }

    float Ball::GetRadius()
    {
        return radius;
    }
}
