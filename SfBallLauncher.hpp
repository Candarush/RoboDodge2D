#pragma once
#include <SFML/Graphics.hpp>
#include "Surface.hpp"
#include "SfBall.hpp"
#include "BallLauncher.hpp"
#include <vector>
#include <cmath>

namespace RoboDodge
{
    class SfBallLauncher : public BallLauncher
    {
        sf::RectangleShape shape;
        std::vector<SfBall> balls;
    public:
        SfBallLauncher(float ix, float iy, float iballRadius);
        void Shoot(float angle, float ballSpeed);
        void UpdateBalls(Surface border, float timeElapsed);
        float GetX();
        float GetY();
        sf::RectangleShape GetShape();
        void DisplayBalls(sf::RenderWindow* window);
    };
}
