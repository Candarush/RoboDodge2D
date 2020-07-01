#include "SfSurface.hpp"

namespace RoboDodge
{
    SfSurface::SfSurface(float iwidth, float iheight, float ioffset_w, float ioffset_h) : Surface(iwidth, iheight, ioffset_w, ioffset_h)
    {
        shape = sf::RectangleShape(sf::Vector2f(iwidth, iheight));
        shape.setPosition(ioffset_w, ioffset_w);
        shape.setFillColor(sf::Color(50,150,50));
    }

    bool SfSurface::IsInsideBox(float ix, float iy)
    {
        return Surface::IsInsideBox(ix, iy);
    }

    sf::RectangleShape SfSurface::GetShape()
    {
        return shape;
    }
}
