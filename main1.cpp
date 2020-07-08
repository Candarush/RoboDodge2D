
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "SfSurface.hpp"
#include "SfRobot.hpp"
#include "SfBall.hpp"
#define M_PI 3.14159 
using namespace RoboDodge;
using namespace std;

int main(int argc, char const** argv)
{
    int choice;
    float width = 300;
    float height = 300;
    float speed = 100;
    int shotAtTime = 0;
    sf::Clock shootClock;
    sf::Clock clock;
    float deltaTime = 0;

    SfSurface ground(width,height,0,0);
    SfRobot robot(25,25,width/8, height-25, speed, speed);
    SfBall ball(10, width / 2 + 100, height / 2 - 100, 90, 120);
    cout << "Choose the robot's mode:\n1. Catch\n2. Dodge" << endl;
    cin >> choice;
    sf::RenderWindow window(sf::VideoMode(width, height), "RoboDodge");
    
    while (window.isOpen())
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
       if (robot.GetAP() == false) {
           robot.Control(&event, robot.GetAP(), deltaTime, ground);
       }
        ball.UpdatePosition(deltaTime, ground);
        if ((robot.Danger(ball) == true)&&(robot.ballCatch(choice) == false)) {
            robot.Dodge(ball, deltaTime, ground);
            robot.PutAP(false);
        }
        else if ((robot.Danger(ball) == false)&&(robot.ballCatch(choice) == true)) {
            robot.Catch(ball, deltaTime, ground);
        }
        window.clear();
        
        window.draw(ground.GetShape());
        window.draw(ball.GetShape());
        window.draw(robot.GetShape());
        
        window.display();
        
        deltaTime = clock.restart().asSeconds();
    }

    return EXIT_SUCCESS;
}
