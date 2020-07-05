#include "Robot.hpp"

namespace RoboDodge
{
    Robot::Robot(float iwidth, float iheight, float ix, float iy, float ispeedx)
    {
        width = iwidth;
        height = iheight;
        x = ix;
        y = iy;
        speedx = ispeedx;
        autopilot = false;
    }

    void Robot::Move(float ix, float deltaTime, Surface ground)
    {
        if ((x - width  > 0) && (ix < 0)) {
            x -= speedx * deltaTime;
        };
        if (((x + width) < ground.GetWidth()) && (ix > 0)) {
            x += speedx * deltaTime;
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
    bool Robot::GetAP()
    {
        return autopilot;
    }

    bool Robot::Danger(Ball ball) {
        float tm, dx, dy, metr, spd;
        dx = ball.GetX() - x;
        dy = ball.GetY() - y;
        metr = sqrt(pow(dx, 2) + pow(dy, 2));
        spd = sqrt(pow(ball.GetSpeedX(), 2) + pow(ball.GetSpeedY(), 2));
        tm = metr / spd;
        
        if (((x - width) < ball.GetSpeedX() * tm + ball.GetX()) &&
            (ball.GetSpeedX() * tm + ball.GetX() < (x + width)) &&
            ((y - width) < ball.GetSpeedY() * tm + ball.GetY()) &&
            (ball.GetSpeedY() * tm + ball.GetY() < (y + width)))
        {
            autopilot = true;
            return true;
        }
        autopilot = false;
        return false;
    }

    void Robot::Dodge(Ball ball, float deltm, Surface ground){
        cout<<"Уворачиваюсь!"<<endl;
        
        if (ball.GetSpeedX()>0)
        {
            Move(-1, deltm, ground);
        }
        else
        {
            Move(1, deltm, ground);
        }
    }
}
