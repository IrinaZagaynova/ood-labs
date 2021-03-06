#pragma once
#include "modern_graphics_lib.h"
#include "graphics_lib.h"

namespace app
{
    class CModernGraphicsClassAdapter : public graphics_lib::ICanvas, protected modern_graphics_lib::CModernGraphicsRenderer
    {
    public:
        CModernGraphicsClassAdapter(ostream& strm)
            : CModernGraphicsRenderer(strm)
            , m_point(0, 0)
            , m_color(0, 0, 0, 1)
        {
            BeginDraw();
        }

        void SetColor(uint32_t rgbColor)
        {
            float r = float((rgbColor >> 16) & 0xff) / 255.0f;
            float g = float((rgbColor >> 8) & 0xff) / 255.0f;
            float b = float(rgbColor & 0xff) / 255.0f;
            m_color = modern_graphics_lib::CRGBAColor(r, g, b, 1);
        }
        void MoveTo(int x, int y)
        {
            m_point = { x, y };
        }
        void LineTo(int x, int y)
        {
            DrawLine(m_point, { x, y }, m_color);
            MoveTo(x, y);
        }

    private:
        modern_graphics_lib::CPoint m_point;
        modern_graphics_lib::CRGBAColor m_color;
    };
}