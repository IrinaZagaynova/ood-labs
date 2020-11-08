#pragma once
#include "modern_graphics_lib.h"
#include "graphics_lib.h"

namespace app
{
    class CModernGraphicsObjectAdapter : public graphics_lib::ICanvas
    {
    public:
        CModernGraphicsObjectAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
            : m_renderer(renderer)
            , m_point(0, 0)
            , m_color(0, 0, 0, 1)
        {
        }

        void SetColor(uint32_t rgbColor)
        {
            float r = float((rgbColor >> 16) & 0xFF) / 255;
            float g = float((rgbColor >> 8) & 0xFF) / 255;
            float b = float(rgbColor & 0xFF) / 255;
            m_color = modern_graphics_lib::CRGBAColor(r, g, b, 1);
        }
        void MoveTo(int x, int y)
        {
            m_point = { x, y };
        }
        void LineTo(int x, int y)
        {
            m_renderer.DrawLine(m_point, { x, y }, m_color);
            MoveTo(x, y);
        }

    private:
        modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
        modern_graphics_lib::CPoint m_point;
        modern_graphics_lib::CRGBAColor m_color;
    };
}