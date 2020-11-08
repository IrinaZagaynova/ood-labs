#pragma once
#include "ModernGraphicsObjectAdapter.h"
#include "shape_drawing_lib.h"

using namespace std;

// Пространство имен приложения (доступно для модификации)
namespace app
{
    void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
    {
        using namespace shape_drawing_lib;
        CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0);
        CRectangle rectangle({ 30, 40 }, 18, 24, 0xff00ff);

        painter.Draw(triangle);
        painter.Draw(rectangle);
    }

    void PaintPictureOnCanvas()
    {
        graphics_lib::CCanvas simpleCanvas;
        shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
        PaintPicture(painter);
    }

    void PaintPictureOnModernGraphicsRenderer()
    {
        modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
        CModernGraphicsObjectAdapter adapter(renderer);
        shape_drawing_lib::CCanvasPainter painter(adapter);
        renderer.BeginDraw();
        PaintPicture(painter);
    }
}