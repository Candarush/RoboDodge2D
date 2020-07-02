#pragma once
#include "Robot.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace RoboDodge
{
    class SfRobot : public Robot
    {
        sf::RectangleShape shape;
    public:
        SfRobot(float iwidth, float iheight, float ix, float iy, float ispeedx, float ispeedy);
        void Move(float ispeedx, float ispeedy);
        float GetX();
        float GetY();
        float GetSpeedX();
        void PutSpeedX(float ispeed);
        float GetTime();
        void PutAP(bool iauto);
        void Control(sf::Event *ev, bool iauto, float deltm, float wdth);
        void Dodge(float iballx, float ibally, float iballspeedx, float iballspeedy, float iradius, float deltm);
        sf::RectangleShape GetShape();
        sf::RectangleShape setPosition();
    };
}
