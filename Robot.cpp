#include "Robot.hpp"

namespace RoboDodge
{
    Robot::Robot(float iwidth, float iheight, float ix, float iy, float ispeedx, bool iisCatching)
    {
        width = iwidth;
        height = iheight;
        x = ix;
        y = iy;
        speedx = ispeedx;
        autopilot = false;
        isCatching = iisCatching;
    }

    void Robot::Move(float ix, float deltaTime, Surface ground)
    {
        if ((x - width/2  > 0) && (ix < 0)) {
            x -= speedx * deltaTime;
        };
        if (((x + width/2) < ground.GetWidth()) && (ix > 0)) {
            x += speedx * deltaTime;
        };
    }

    float Robot::GetX()
    {
        return x;
    }

    float Robot::GetWidth()
    {
        return width;
    }
    
    float Robot::GetHeight()
    {
        return height;
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

    bool Robot::Danger(Ball ball, float border) {
        if (isCatching)
            return false;
        
        float tm, dx, dy, metr, spd;
        dx = ball.GetX() - x;
        dy = ball.GetY() - y;
        metr = sqrt(pow(dx, 2) + pow(dy, 2));
        spd = sqrt(pow(ball.GetSpeedX(), 2) + pow(ball.GetSpeedY(), 2));
        tm = metr / spd;
        
        if (((x - width - border) < ball.GetSpeedX() * tm + ball.GetX()) &&
            (ball.GetSpeedX() * tm + ball.GetX() < (x + width + border)) &&
            ((y - width - border) < ball.GetSpeedY() * tm + ball.GetY()) &&
            (ball.GetSpeedY() * tm + ball.GetY() < (y + width + border)))
        {
            autopilot = true;
            return true;
        }
        autopilot = false;
        return false;
    }

    void Robot::Dodge(Ball ball, float deltm, Surface ground){
        if (ball.GetSpeedX()>0)
        {
            Move(-1, deltm, ground);
        }
        else
        {
            Move(1, deltm, ground);
        }
    }

    void Robot::Catch(vector<Ball> iballs, Surface ground, float deltm)
    {
        if (isCatching)
        {
            float maxY = 0;
            Ball ballToCatch(0,0,0,0,0);
            
            for (int i = 0; i < iballs.size(); i++)
            {
                if (iballs[i].GetSpeedY() > 0 && iballs[i].GetY() > maxY)
                {
                    ballToCatch = iballs[i];
                    maxY = iballs[i].GetY();
                }
            }
            
            if (ballToCatch.GetSpeedY() > 0)
            {
                if (ballToCatch.GetX() < x - width/3)
                {
                    Move(-1, deltm, ground);
                }
                if (ballToCatch.GetX() > x + width/3)
                {
                    Move(1, deltm, ground);
                }
            }
        }
    }
}
