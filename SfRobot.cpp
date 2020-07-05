#include "SfRobot.hpp"
namespace RoboDodge
{
    SfRobot::SfRobot(float iwidth, float iheight, float ix, float iy, float ispeedx, float ispeedy) : Robot(iwidth, iheight, ix, iy, ispeedx, ispeedy)
    {
        shape = sf::RectangleShape(sf::Vector2f(iwidth, iheight));
        shape.setFillColor(sf::Color(0, 0, 255));
        shape.setPosition(ix,iy);
    }

    void SfRobot::Move(float ispeedx, float ispeedy, Surface ground)
    {
        Robot::Move(ispeedx, ispeedy, ground);
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
    
    float SfRobot::GetSpeedY()
    {
        return Robot::GetSpeedY();
    }

    float SfRobot::GetTime()
    {
        return Robot::GetTime();
    }

    void SfRobot::PutSpeedX(float ispeed)
    {
        Robot::PutSpeedX(ispeed);
    }

    void SfRobot::PutAP(bool iauto)
    {
        Robot::PutAP(iauto);
    }

    bool SfRobot::GetAP()
    {
        return Robot::GetAP();
    }

    bool SfRobot::Danger(float iballx, float ibally, float iradius, float iballspeedx, float iballspeedy)
    {
        return Robot::Danger(iballx, ibally, iradius, iballspeedx, iballspeedy);
    }
    void SfRobot::Control(sf::Event* ev, bool iauto, float deltm, Surface ground){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                    Move(-GetSpeedX() * deltm, 0, ground);
                    shape.setPosition(GetX(), GetY());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    Move(GetSpeedX() * deltm, 0, ground);
                    shape.setPosition(GetX(), GetY());
            }
            /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                    Move(0, -GetSpeedY() * deltm, ground);
                    shape.setPosition(GetX(), GetY());
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    Move(0, GetSpeedY() * deltm, ground);
                    shape.setPosition(GetX(), GetY());
            }*/
    }
    void SfRobot::Dodge(float iballspeedx, float iballspeedy, float deltm, Surface ground){
        Move(-iballspeedy * deltm, 0, ground);
        shape.setPosition(GetX(), GetY());
    }
    sf::RectangleShape SfRobot::GetShape()
    {
        return shape;
    }
}
