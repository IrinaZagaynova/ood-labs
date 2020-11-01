#include "Canvas.h"
#include "Designer.h"
#include "PictureDraft.h"
#include "Painter.h"
#include "ShapeFactory.h"
#include <sstream>
#include <GLFW/glfw3.h>

int main()
{
    std::cout << "Use: \n" <<
        "<rectangle> <left corner top x> <left top corner y> <width> <height> <color>\n" <<
        "<triangle> <vertex1 x> <vertex1 y> <vertex2 x> <vertex2 y> <vertex3 x> <vertex3 y> <color>\n" <<
        "<ellipse> <center x> <center y> <horizontal radius> <vertical radius> <color>\n" <<
        "<regular polygon> <center x> <center y> <vertex count> <radius> <color>\n\n";

    CShapeFactory factory;
    CDesigner designer(factory);
    CPictureDraft draft = designer.CreateDraft(std::cin);

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(900, 600, "", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    CPainter painter;
    CCanvas canvas;

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_LINE_SMOOTH);
        
        painter.DrawPicture(draft, canvas);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

