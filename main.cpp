
#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "SfSurface.hpp"
#include "SfRobot.hpp"
#include "SfBallLauncher.hpp"
#include "Detector.hpp"


using namespace RoboDodge;
using namespace std;
using namespace sf;
using namespace cv;

int main(int argc, char const** argv)
{
    bool exit = false;
    
    float width = 300;
    float height = 300;
    
    SfSurface ground(300,300,0,0);
    
    sf::RenderWindow window(sf::VideoMode(1500, 500), "RoboDodge");
    
    VideoCapture cap("BallTestLine.mp4");
    if(!cap.isOpened()){
      cout << "Ошибка, видео не открыто." << endl;
      return -1;
    }
    Detector detector(&cap, width, height);
    
    while (window.isOpen() && !detector.GetFrame().empty())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }
        
        detector.FindBall();
        SfBall ball(15, detector.GetBallX(), detector.GetBallY(), 0, 0);
        SfRobot robot(15,15,detector.GetRobotX(), detector.GetRobotY()-8, 0, 0);
        
        
        window.clear();
        
        window.draw(ground.GetShape());
        window.draw(ball.GetShape());
        window.draw(robot.GetShape());
        detector.DrawResultAt(&window,320,20);
        
        window.display();
    }

    return 0;
}
