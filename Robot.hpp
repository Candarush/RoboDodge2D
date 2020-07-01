#pragma once

namespace RoboDodge
{
    class Robot
    {
        bool autopilot;
        float width, height, x, y, speedx, speedy, time;
    public:
        Robot(float iwidth, float iheight, float ix, float iy, float ispeedx, float ispeedy);
        void Move(float ispeedx, float ispeedy);
        float GetX();
        float GetY();
        float GetWidth();
        void PutWidth(float iwidth);
        float GetSpeedX();
        void PutSpeedX(float ispeed);
        float GetTime();
        void PutTimeX(float itime);
        void PutAP(bool iauto);
        bool GetAP();
    };
}
