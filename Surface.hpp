#pragma once

namespace RoboDodge
{
    class Surface
    {
        float width, height, offset_w, offset_h;
    public:
        Surface(float iwidth, float iheight, float ioffset_w, float ioffset_h);
        bool IsInsideBox(float x, float y);
    };
}
