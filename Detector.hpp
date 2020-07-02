#pragma once
#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;
using namespace sf;

namespace RoboDodge
{
    class Detector
    {
        VideoCapture* capture;
        Mat frame, resultMat;
        Sprite sprite;
        float surfaceX, surfaceY;
        cv::Point ballPos, robotPos;
        cv::Point screenLineLeft, screenLineRight;
    public:
        Detector(VideoCapture* icapture, float isurfaceX, float isurfaceY);
        void FindBall();
        float GetBallX();
        float GetBallY();
        float GetRobotX();
        float GetRobotY();
        void DrawResultAt(RenderWindow* window, float posx, float posy);
        Mat GetFrame();
    };
}
