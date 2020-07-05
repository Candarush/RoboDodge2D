#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include "Surface.hpp"
#include "Robot.hpp"
#include "Ball.hpp"
#include "Detector.hpp"
#include "OpenGLRenderer.hpp"

#include <GL/glut.h>

using namespace RoboDodge;
using namespace std;
using namespace cv;

class Model
{
public:
    static vector<Ball> balls;
    static Surface ground;
    static Robot robot;
    static Detector detector;
    
    // Called every frame. Outputs current cycle time "deltaTime" and current opengl picture "frame".
    static void Update(float deltaTime, Mat frame)
    {
        // Detector update
        detector.FindBall(frame);
        imshow("OpenCV Detector",detector.GetResult());
        waitKey(1);
        
        // Balls update
        for (int i = 0; i<balls.size(); i++)
        {
            // Robot update
            if (robot.Danger(balls[i])) {
                robot.Dodge(balls[i], deltaTime, ground);
            }
            
            balls[i].UpdatePosition(deltaTime, ground);
        }
    }
};

vector<Ball> Model::balls;
Surface Model::ground(400, 400, 0, 0);
Robot Model::robot(40,40,50, ground.GetHeight(),1);
Detector Model::detector(ground.GetWidth(),ground.GetHeight());

int main(int argc, char **argv)
{
    Model m;
    
    m.balls.push_back(Ball(10,50,50, 0.5,1));
    
    OpenGLRenderer renderer(argc, argv, 300,300, m.Update, &(m.balls), &(m.robot), &(m.ground));
    
    return 0;
}
