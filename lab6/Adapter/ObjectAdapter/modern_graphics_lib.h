#pragma once
#include <iostream>
#include <boost/format.hpp>

using namespace std;

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
    class CPoint
    {
    public:
        CPoint(int x, int y) :x(x), y(y) {}
        int x, y;
    };

    // Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
    class CRGBAColor
    {
    public:
        CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
        float r, g, b, a;
    };

    // Класс для современного рисования графики
    class CModernGraphicsRenderer
    {
    public:
        CModernGraphicsRenderer(ostream& strm) 
            : m_out(strm)
        {
        }

        ~CModernGraphicsRenderer()
        {
            if (m_drawing) // Завершаем рисование, если оно было начато
            {
                EndDraw();
            }
        }

        void BeginDraw()
        {
            if (m_drawing)
            {
                throw logic_error("Drawing has already begun");
            }
            m_out << "<draw>" << endl;
            m_drawing = true;
        }

        // Выполняет рисование линии
        void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& color)
        {
            if (!m_drawing)
            {
                throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
            }

            m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)") % start.x % start.y % end.x % end.y << endl
                << boost::format(R"(    <color r="%1%" g="%2%" b="%3%" a="%4%" />)") % color.r % color.g % color.b % color.a << endl
                << "  </line>" << endl;
        }

        void EndDraw()
        {
            if (!m_drawing)
            {
                throw logic_error("Drawing has not been started");
            }
            m_out << "</draw>" << endl;
            m_drawing = false;
        }

    private:
        ostream& m_out;
        bool m_drawing = false;
    };
}
