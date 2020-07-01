#include "Robot.hpp"
#include <cmath>

namespace RoboDodge
{
    Robot::Robot(float iwidth, float iheight, float ix, float iy, float ispeedx, float ispeedy)
    {
        width = iwidth;
        height = iheight;
        x = ix;
        y = iy;
        speedx = ispeedx;
        speedy = ispeedy;
        autopilot = false;
    }

    void Robot::Move(float ix, float iy)
    {
        x += ix;
        y += iy;
    }

    float Robot::GetX()
    {
        return x;
    }

    float Robot::GetY()
    {
        return y;
    }
    float Robot::GetSpeedX()
    {
        return speedx;
    }
    float Robot::GetWidth()
    {
        return width;
    }
    void Robot::PutWidth(float iwidth)
    {
        width = iwidth;
    }
    void Robot::PutSpeedX(float ispeed)
    {
        speedx = ispeed;
    }
    float Robot::GetTime()
    {
        return time;
    }
    void Robot::PutTimeX(float itime)
    {
        time = itime;
    }
    void Robot::PutAP(bool iauto)
    {
        autopilot = iauto;
    }
    bool Robot::GetAP()
    {
        return autopilot;
    }
}