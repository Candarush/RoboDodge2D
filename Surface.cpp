#include "Surface.hpp"

namespace RoboDodge
{
    Surface::Surface(float iwidth, float iheight, float ioffset_w, float ioffset_h)
    {
        width = iwidth;
        height = iheight;
        offset_w = ioffset_w;
        offset_h = ioffset_h;
    }

    bool Surface::IsInsideBox(float x, float y)
    {
        if (x > width + offset_w || x < offset_w)
        {
            return false;
        }
        if (y > height + offset_h || y < offset_h)
        {
            return false;
        }
        return true;
    }

    float Surface::GetWidth()
    {
        return width;
    }

    float Surface::GetHeight()
    {
        return height;
    }
}
