#include <GLFW/glfw3.h>
#include "Slide.h"
#include "Canvas.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Group.h"

void CreateShapesOnSlide(CSlide& slide)
{
    CRectangle chimney({ -0.4, 0.4 }, 0.05, 0.3);
    chimney.GetFillStyle()->SetColor({ 0, 1, 0, 1 });
    chimney.GetLineStyle()->SetColor({ 0, 0, 1, 1 });

    CTriangle roof({ -0.5, 0.3 }, { -0.8, 0 }, { -0.2, 0 });
    roof.GetFillStyle()->SetColor({ 1, 0, 0, 1 });
    roof.GetLineStyle()->SetColor({ 1, 0, 0, 1 });

    auto roofWithChimney = std::make_shared<CGroup>();
    roofWithChimney->InsertShape(std::make_shared<CRectangle>(chimney), 0);
    roofWithChimney->InsertShape(std::make_shared<CTriangle>(roof), 1);

    CRectangle square({ -0.75, 0 }, 0.5, 0.5);

    auto house = std::make_shared<CGroup>();
    house->InsertShape(roofWithChimney, 0);
    house->InsertShape(std::make_shared<CRectangle>(square), 1);
    house->GetLineStyle()->SetColor({ 0, 0, 1, 1 });
    house->SetFrame({ -0.8, 0.1, 0.6, 0.7 });
    house->GetLineStyle()->Enable(true);
    house->GetFillStyle()->Enable(true);

    CEllipse lake({ 0.5, -0.4 }, 0.3, 0.1);
    lake.GetFillStyle()->SetColor({ 0, 1, 1, 1 });
    lake.GetFillStyle()->Enable(true);

    CEllipse sun({ 0.5, 0.7 }, 0.1, 0.1);
    sun.GetFillStyle()->SetColor({ 1, 1, 0, 1 });
    sun.GetFillStyle()->Enable(true);

    slide.InsertShape(house, 0);
    slide.InsertShape(std::make_shared<CEllipse>(lake), 1);
    slide.InsertShape(std::make_shared<CEllipse>(sun), 2);
}

void DrawSlide(const CSlide& slide, CCanvas& canvas)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return;
    }

    window = glfwCreateWindow(slide.GetWidth(), slide.GetHeight(), "", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glClearColor(slide.GetBackgroundColor().r, slide.GetBackgroundColor().g, slide.GetBackgroundColor().b, slide.GetBackgroundColor().a);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        slide.Draw(canvas);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
}

int main()
{
    CSlide slide(900, 750, RGBAColor(1, 1, 1, 0));
    CreateShapesOnSlide(slide);
    CCanvas canvas;
    DrawSlide(slide, canvas);
}
