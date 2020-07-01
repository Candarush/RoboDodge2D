#pragma once

namespace RoboDodge
{
    class Robot
    {
        float width, height, x, y, speedx, speedy;
    public:
        Robot(float iwidth, float iheight, float ix, float iy);
        void Move(float ix, float iy);
        float GetX();
        float GetY();
    };
}
