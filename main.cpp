#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include "Surface.hpp"
#include "Robot.hpp"
#include "Ball.hpp"
#include "Detector.hpp"
#include "OpenGLRenderer.hpp"
#include "DBclient.hpp"

#include <string>

#include <GL/glut.h>

using namespace RoboDodge;
using namespace std;
using namespace cv;

class Model
{
    static DBclient database;
    static Detector detector;
    
public:
    
    static Surface ground;
    static Robot robot;
    static vector<Ball> balls;
    
    // Called every frame. Outputs current cycle time "deltaTime" and current opengl picture "frame".
    static void Update(float deltaTime, Mat frame)
    {
        // Detector update
        detector.FindBall(frame, deltaTime);
        imshow("OpenCV Detector",detector.GetResult());
        waitKey(1);
        
        // Balls update
        for (int i = 0; i<balls.size(); i++)
        {
            balls[i].UpdatePosition(deltaTime, ground);
            string ballName = "RealBall["+to_string(i)+"]";
            database.SendPosition(ballName, balls[i].GetX(), balls[i].GetY());
        }

        // Catch ball if catching
        robot.Catch(*detector.GetBalls(), ground, deltaTime);
        
        // Robot update
        for (int i = 0; i < detector.GetBalls()->size(); i++)
        {
            string ballName = "ApproximateBall["+to_string(i)+"]";
            database.SendPosition(ballName, balls[i].GetX(), balls[i].GetY());
            
            if (robot.Danger(detector.GetBalls()->at(i), 100)) {
                robot.Dodge(detector.GetBalls()->at(i), deltaTime, ground);
            }

        }
    }
};

DBclient Model::database("127.0.0.1", 8086,"RoboDodgeDB");
vector<Ball> Model::balls;
Surface Model::ground(400, 400, 0, 0);
Robot Model::robot(40,15,50, ground.GetHeight(),1, false);
Detector Model::detector(ground.GetWidth(),ground.GetHeight(), &balls, &robot);

int main(int argc, char **argv)
{
    Model m;
    
    m.balls.push_back(Ball(10,50,50, 0.3,1.5));
    //m.balls.push_back(Ball(10,250,250, -0.2,1.3));
    
    OpenGLRenderer renderer(argc, argv, 350,350, m.Update, &(m.balls), &(m.robot), &(m.ground));
    
    return 0;
}
