#pragma once
#include <opencv2/opencv.hpp>
#include "Ball.hpp"
#include "Robot.hpp"
#include <string>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;

namespace RoboDodge
{
    class Detector
    {
        vector<Ball>* realBalls;
        Robot* realRobot;
        Mat resultMat;
        float surfaceX, surfaceY;
        vector<Ball> balls;
        cv::Point robotPos, screenLineLeft, screenLineRight;
    public:
        Detector(float isurfaceX, float isurfaceY, vector<Ball>* realBalls, Robot* realRobot);
        void FindBall(cv::Mat frame, float deltaTime);
        vector<Ball>* GetBalls();
        float GetRobotX();
        float GetRobotY();
        Mat Get2DResult();
        Mat GetResult();
    };
}
