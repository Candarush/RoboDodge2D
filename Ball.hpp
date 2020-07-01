#pragma once

namespace RoboDodge
{
    class Ball
    {
        float radius, x, y, xspeed, yspeed;
    public:
        Ball(float radius, float ix, float iy, float xspeed, float yspeed);
        void UpdatePosition(float timeElapsed);
        float GetX();
        float GetY();
        float GetSpeedX();
        float GetSpeedY();
        float GetRadius();
    };
}
