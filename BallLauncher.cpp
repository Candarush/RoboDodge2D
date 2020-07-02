#include "BallLauncher.hpp"
namespace RoboDodge
{
    BallLauncher::BallLauncher(float ix, float iy, float iballRadius)
    {
        ballRadius = iballRadius;
        x = ix;
        y = iy;
    }

    void BallLauncher::Shoot(float angle, float ballSpeed)
    {
        Ball ball(ballRadius, x, y, ballSpeed*cos(angle*M_PI/180), ballSpeed*sin(angle*M_PI/180));
        balls.push_back(ball);
    }

    void BallLauncher::UpdateBalls(Surface border, float timeElapsed)
    {
        for(int i = 0; i<balls.size(); i++)
        {
            balls[i].UpdatePosition(timeElapsed, border);
            if (balls.size()>10)
            {
                balls.erase(balls.begin()+0);
            }
        }
    }

    float BallLauncher::GetX()
    {
        return x;
    }

    float BallLauncher::GetY()
    {
        return y;
    }

    float BallLauncher::GetBallRadius()
    {
        return ballRadius;
    }
}
