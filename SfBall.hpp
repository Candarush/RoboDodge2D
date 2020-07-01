#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.hpp"

namespace RoboDodge
{
    class SfBall : public Ball
    {
        sf::CircleShape shape;
    public:
        SfBall(float iradius, float ix, float iy, float ixspeed, float iyspeed);
        void UpdatePosition(float timeElapsed);
        float GetX();
        float GetY();
        sf::CircleShape GetShape();
    };
}
