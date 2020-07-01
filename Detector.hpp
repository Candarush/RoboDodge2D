#pragma once
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
using namespace cv;

namespace RoboDodge
{
    class Detector
    {
        VideoCapture* capture;
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
    };
}
