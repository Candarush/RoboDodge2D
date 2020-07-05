#pragma once
#include "Robot.hpp"
#include <SFML/Graphics.hpp>

namespace RoboDodge
{
    class SfRobot : public Robot
    {
        sf::RectangleShape shape;
    public:
        SfRobot(float iwidth, float iheight, float ix, float iy, float ispeedx, float ispeedy);
        void Move(float ispeedx, float ispeedy, Surface ground);
        float GetX();
        float GetY();
        float GetSpeedX();
        float GetSpeedY();
        void PutSpeedX(float ispeed);
        float GetTime();
        bool GetAP();
        void PutAP(bool iauto);
        bool Danger(float iballx, float ibally, float iradius, float iballspeedx, float iballspeedy);
        void Control(sf::Event *ev, bool iauto, float deltm, Surface ground);
        void Dodge(float iballspeedx, float iballspeedy, float deltm, Surface ground);
        sf::RectangleShape GetShape();
        sf::RectangleShape setPosition();
    };
}

