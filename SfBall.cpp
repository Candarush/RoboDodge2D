#include "SfBall.hpp"

namespace RoboDodge
{
    SfBall::SfBall(float iradius, float ix, float iy, float ixspeed, float iyspeed) : Ball(iradius, ix, iy, ixspeed, iyspeed)
    {
        shape = sf::CircleShape(iradius);
        shape.setFillColor(sf::Color(255,0,0));
        shape.setPosition(ix, iy);
    }

    void SfBall::UpdatePosition(float timeElapsed, Surface ground)
    {
        
        Ball::UpdatePosition(timeElapsed, ground);
        shape.setPosition(Ball::GetX(), Ball::GetY());
    }

    float SfBall::GetX()
    {
        return Ball::GetX();
    }

    float SfBall::GetY()
    {
        return Ball::GetY();
    }

    sf::CircleShape SfBall::GetShape()
    {
        return shape;
    }
}
