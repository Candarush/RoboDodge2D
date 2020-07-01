#pragma once
#include "Surface.hpp"
#include "Ball.hpp"
#include <vector>
#include <cmath>

namespace RoboDodge
{
    class BallLauncher
    {
        float ballRadius,faceAngle, x, y;
        
    public:
        std::vector<Ball> balls;
        BallLauncher(float ix, float iy, float iballRadius);
        void Shoot(float angle, float ballSpeed);
        void UpdateBalls(Surface border, float timeElapsed);
        float GetX();
        float GetY();
        float GetBallRadius();
    };
}
