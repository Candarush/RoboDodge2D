#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "Ball.hpp"
#include "Surface.hpp"

using namespace std;

namespace RoboDodge
{
    class Robot
    {
        bool autopilot;
        float width, height, x, y, speedx, time;
    public:
        bool isCatching;
        
        Robot(float iwidth, float iheight, float ix, float iy, float ispeedx, bool iisCatching);
        void Move(float ispeedx, float deltaTime, Surface ground);
        float GetX();
        float GetY();
        float GetWidth();
        float GetHeight();
        float GetSpeedX();
        bool GetAP();
        bool Danger(Ball ball, float border);
        void Dodge(Ball ball, float deltm, Surface ground);
        void Catch(vector<Ball> balls, Surface ground, float deltm);
    };
}
