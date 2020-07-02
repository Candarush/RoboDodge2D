
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "SfSurface.hpp"
#include "SfRobot.hpp"
#include "SfBallLauncher.hpp"
#define M_PI 3.14159 
using namespace RoboDodge;
using namespace std;

int main(int argc, char const** argv)
{
    float width = 300;
    float height = 300;
    float speed = 100;
    int shotAtTime = 0;
    sf::Clock shootClock;
    sf::Clock clock;
    float deltaTime = 0.1;
    bool autopilot;

    SfSurface ground(width,height,0,0);
    SfRobot robot(25,25,width/4, (height-25), speed, 0);
    SfBallLauncher launcher(width/2+100, height/2-100, 5);
    
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
        autopilot = robot.GetAP();
        robot.Control(&event, autopilot, deltaTime, width);
        if ((int)shootClock.getElapsedTime().asSeconds() % 3 == 0 && shotAtTime != (int)shootClock.getElapsedTime().asSeconds())
        {   
            shotAtTime = (int)shootClock.getElapsedTime().asSeconds();
            float angle = atan2(launcher.GetY() - robot.GetY(), launcher.GetX() - robot.GetX())*180/M_PI+180;
            launcher.Shoot(angle,200);
        }
        
        launcher.UpdateBalls(ground, deltaTime);
        
        window.clear();
        
        window.draw(ground.GetShape());
        window.draw(launcher.GetShape());
        window.draw(robot.GetShape());
        
        launcher.DisplayBalls(&window);
        
        window.display();
        
        deltaTime = clock.restart().asSeconds();
    }

    return EXIT_SUCCESS;
}
