#include "Canvas.h"
#define _USE_MATH_DEFINES
#include <math.h>

void CCanvas::SetColor(Color color)
{
    switch (color)
    {
    case Color::Green:
        m_color = RGBcolor(0, 1, 0);
        break;
    case Color::Red:
        m_color = RGBcolor(1, 0, 0);
        break;
    case Color::Blue:
        m_color = RGBcolor(0, 0, 1);
        break;
    case Color::Yellow:
        m_color = RGBcolor(1, 1, 0);
        break;
    case Color::Pink:
        m_color = RGBcolor(1, 0, 1);
        break;
    case Color::Black:
        m_color = RGBcolor(0, 0, 0);
        break;
    }
}

void CCanvas::DrawLine(SPoint from, SPoint to)
{
	glLineWidth(2);
    glColor3d(m_color.red, m_color.green, m_color.blue);

	glBegin(GL_LINES);
	glVertex2d(from.x, from.y);
	glVertex2d(to.x, to.y);
	glEnd();
}

void CCanvas::DrawEllipse(SPoint center, double horizontalRadius, double verticalRadius)
{
    glLineWidth(2);
    glColor3d(m_color.red, m_color.green, m_color.blue);

    double xAngle = 1;
    double yAngle = 0;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        glVertex2d(xAngle * horizontalRadius + center.x, yAngle * verticalRadius + center.y);

        double t = xAngle;
        xAngle = cos(2 * M_PI / 360) * xAngle - sin(2 * M_PI / 360) * yAngle;
        yAngle = sin(2 * M_PI / 360) * t + cos(2 * M_PI / 360) * yAngle;
    }
    glEnd();
}
