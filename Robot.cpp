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

    void Robot::Move(float ix, float iy, Surface ground)
    {
        if ((GetX() > 0) && (ix < 0)) {
            x += ix;
        };
        if (((GetX() + GetWidth()) < ground.GetWidth()) && (ix > 0)) {
            x += ix;
        };
        if ((GetY() > 0) && (iy < 0)) {
            y += iy;
        };
        if (((GetY() + GetWidth()) < ground.GetHeight()) && (iy > 0)) {
            y += iy;
        }; 
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
    float Robot::GetSpeedY()
    {
        return speedy;
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
    bool Robot::Danger(float iballx, float ibally, float iradius, float iballspeedx, float iballspeedy) {
        float tm, dx, dy, metr, spd;
        dx = iballx - GetX();
        dy = ibally - GetY();
        metr = sqrt(pow(dx, 2) + pow(dy, 2));
        spd = sqrt(pow(iballspeedx, 2) + pow(iballspeedy, 2));
        tm = metr / spd;
        if (((GetX() - GetWidth()) < iballspeedx * tm + iballx) && (iballspeedx * tm + iballx < (GetX() + GetWidth())) && ((GetY() - GetWidth()) < iballspeedy * tm + ibally) && (iballspeedy * tm + ibally < (GetY() + GetWidth()))) {
            PutAP(true);
            return true;
        }
    }
}
