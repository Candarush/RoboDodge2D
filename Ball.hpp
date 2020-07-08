#pragma once
#include "Surface.hpp"

namespace RoboDodge
{
    class Ball
    {
        float radius, x, y, xspeed, yspeed;
        void Bounce(Surface ground);
    public:
        Ball(float radius, float ix, float iy, float xspeed, float yspeed);
        void UpdatePosition(float timeElapsed, Surface ground);
        float GetX();
        float GetY();
        float GetSpeedX();
        float GetSpeedY();
        float GetRadius();
    };
}
