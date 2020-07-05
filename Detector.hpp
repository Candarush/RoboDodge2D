#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;

namespace RoboDodge
{
    class Detector
    {
        Mat resultMat;
        float surfaceX, surfaceY;
        cv::Point ballPos, robotPos;
        cv::Point screenLineLeft, screenLineRight;
    public:
        Detector(float isurfaceX, float isurfaceY);
        void FindBall(cv::Mat frame);
        float GetBallX();
        float GetBallY();
        float GetRobotX();
        float GetRobotY();
        Mat GetResult();
    };
}
