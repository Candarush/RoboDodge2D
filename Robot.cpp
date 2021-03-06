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
    void Robot::PutAP(bool iauto)
    {
        autopilot = iauto;
    }
    bool Robot::GetAP()
    {
        return autopilot;
    }
    bool Robot::ballCatch(int choice) {
        switch (choice) {
        case 1:
            return true;
        case 2:
            return false;
        }
    }
    void Robot::Catch(Ball ball, float deltm, Surface ground) {
        autopilot = true;
        Move(ball.GetSpeedX() * deltm, 0, ground);
        shape.setPosition(x, y);
    }
    bool Robot::Danger(Ball ball) {
        float tm, dx, dy, metr, spd;
        dx = ball.GetX() - GetX();
        dy = ball.GetY() - GetY();
        metr = sqrt(pow(dx, 2) + pow(dy, 2));
        spd = sqrt(pow(ball.GetSpeedX(), 2) + pow(ball.GetSpeedY(), 2));
        tm = metr / spd;
        if (((GetX() - GetWidth()) < (ball.GetSpeedX() * tm + ball.GetX())) && ((ball.GetSpeedX() * tm + ball.GetX()) < (GetX() + GetWidth())) && ((GetY() - GetWidth()) < (ball.GetSpeedY() * tm + ball.GetY())) && ((ball.GetSpeedY() * tm + ball.GetY()) < (GetY() + GetWidth()))) {
            PutAP(true);
            return true;
        }
    }
}
