#include "Robot.hpp"

namespace RoboDodge
{
    Robot::Robot(float iwidth, float iheight, float ix, float iy)
    {
        width = iwidth;
        height = iheight;
        x = ix;
        y = iy;
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
}
