#pragma once
#include "Ball.hpp"
#include "Robot.hpp"
#include "Surface.hpp"
#include <GL/glut.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

namespace RoboDodge
{
    class OpenGLRenderer
    {
        static float deltaTime, timer;
        
        static vector<Ball>* balls;
        static Robot* robot;
        static float movementDirection;
        static Surface* ground;
        
        static void (*UpdateFunc)(float, Mat frame);
        static void OpenGLUpdate();
        void InitRendering();
        static void HandleResize(int iwidth, int iheight);
        static void UpdateCameraPos();
        static void Draw();
        static void DrawSphere(float radius, float x, float y, float z);
        static void DrawBox(float ox, float oy, float oz, float x, float y, float z);
        static void KeyboardControl(int key, int x, int y);
        static void KeyboardButtonRelease(int key, int x, int y);
    public:
        OpenGLRenderer(int argc, char** argv, float windowWidth, float windowHeight, void (*UpdateFunc)(float, Mat), vector<Ball>* balls, Robot* robot, Surface* ground);
    };
}
