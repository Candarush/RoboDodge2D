#pragma once
#include "Surface.hpp"
#include <SFML/Graphics.hpp>

namespace RoboDodge
{
    class SfSurface : public Surface
    {
        sf::RectangleShape shape;
    public:
        SfSurface(float iwidth, float iheight, float ioffset_w, float ioffset_h);
        bool IsInsideBox(float x, float y);
        sf::RectangleShape GetShape();
    };
}
