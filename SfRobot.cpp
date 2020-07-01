#include "SfRobot.hpp"

namespace RoboDodge
{
    SfRobot::SfRobot(float iwidth, float iheight, float ix, float iy, float ispeedx, float ispeedy) : Robot(iwidth, iheight, ix, iy, ispeedx, ispeedy)
    {
        shape = sf::RectangleShape(sf::Vector2f(iwidth, iheight));
        shape.setFillColor(sf::Color(0, 0, 255));
        shape.setPosition(ix,iy);
    }

    void SfRobot::Move(float ispeedx, float ispeedy)
    {
        Robot::Move(ispeedx, ispeedy);
    }

    float SfRobot::GetX()
    {
        return Robot::GetX();
    }

    float SfRobot::GetY()
    {
        return Robot::GetY();
    }
    
    float SfRobot::GetSpeedX()
    {
        return Robot::GetSpeedX();
    }
    
    float SfRobot::GetTime()
    {
        return Robot::GetTime();
    }

    void SfRobot::PutSpeedX(float ispeed)
    {
        Robot::PutSpeedX(ispeed);
    }

    void SfRobot::Control(sf::Event* ev, bool iauto, float deltm, float wdth){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (GetX() > 0) {
                    Move(-GetSpeedX() * deltm, 0);
                    shape.setPosition(GetX(), GetY());
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                if ((GetX() + GetWidth()) < wdth) {
                    Move(GetSpeedX() * deltm, 0);
                    shape.setPosition(GetX(), GetY());
                }
            }

    }
    void SfRobot::Dodge(float iballx, float ibally, float iballspeedx, float iballspeedy, float iradius, float deltm){
        float tm, dx, dy, metr, spd, col, dodgespeed;
        dx = iballx - GetX();
        dy = ibally - GetY();
        metr = sqrt(pow(dx, 2) + pow(dy, 2));
        spd = sqrt(pow(iballspeedx, 2) + pow(iballspeedy, 2));
        tm = metr / spd;
        if (iradius < GetWidth() / 2) {
            dodgespeed = GetWidth() / 2 / tm;
            PutSpeedX(dodgespeed);
            if (dx > 0) {
                Move(-GetSpeedX() * deltm, 0);
                shape.setPosition(GetX(), GetY());
            }
            else {
                Move(GetSpeedX() * deltm, 0);
                shape.setPosition(GetX(), GetY());
            }
        }
        else {
            dodgespeed = (iradius + 1) / tm;
            PutSpeedX(dodgespeed);
            if (dx > 0) {
                Move(-GetSpeedX() * deltm, 0);
                shape.setPosition(GetX(), GetY());
            }
            else {
                Move(GetSpeedX() * deltm, 0);
                shape.setPosition(GetX(), GetY());
            }
        }
    }
    sf::RectangleShape SfRobot::GetShape()
    {
        return shape;
    }
}
