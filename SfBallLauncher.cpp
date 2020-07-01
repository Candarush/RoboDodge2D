#include "SfBallLauncher.hpp"
#define M_PI 3.14159
namespace RoboDodge
{
    SfBallLauncher::SfBallLauncher(float ix, float iy, float iballRadius) : BallLauncher(ix, iy, iballRadius)
    {
        shape = sf::RectangleShape(sf::Vector2f(iballRadius*4, iballRadius*2));
        shape.setOrigin(iballRadius*1.5, iballRadius);
        shape.setFillColor(sf::Color(150, 0, 0));
        shape.setPosition(ix, iy);
    }

    void SfBallLauncher::Shoot(float angle, float ballSpeed)
    {
        shape.setRotation(angle);
        SfBall ball(BallLauncher::GetBallRadius(), BallLauncher::GetX(), BallLauncher::GetY(), ballSpeed*cos(angle*M_PI/180), ballSpeed*sin(angle*M_PI/180));
        balls.push_back(ball);
    }

    void SfBallLauncher::UpdateBalls(Surface border, float timeElapsed)
    {
        for(int i = 0; i<balls.size(); i++)
        {
            balls[i].UpdatePosition(timeElapsed);
            if (!border.IsInsideBox(balls[i].GetX(), balls[i].GetY()))
            {
                balls.erase(balls.begin()+i);
            }
        }
    }

    float SfBallLauncher::GetX()
    {
        return BallLauncher::GetX();
    }

    float SfBallLauncher::GetY()
    {
        return BallLauncher::GetY();
    }

    sf::RectangleShape SfBallLauncher::GetShape()
    {
        return shape;
    }

    void SfBallLauncher::DisplayBalls (sf::RenderWindow* window)
    {
        for(int i = 0; i<balls.size(); i++)
        {
            window->draw(balls[i].GetShape());
        }
    }
}
