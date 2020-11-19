#include "Canvas.h"
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>

void CCanvas::SetLineColor(RGBAColor color)
{
	m_outlineColor = color;
}

void CCanvas::SetFillColor(RGBAColor color)
{
	m_fillColor = color;
}

void CCanvas::SetLineSize(float lineSize)
{
	m_lineWidth = lineSize;
}

void CCanvas::DrawLine(Point from, Point to)
{
	glLineWidth(5);
	glColor4f(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b, m_outlineColor.a);

	glBegin(GL_LINES);
	glVertex2d(from.x, from.y);
	glVertex2d(to.x, to.y);
	glEnd();
}

void CCanvas::DrawEllipse(Point center, double horizontalRadius, double verticalRadius)
{
	glLineWidth(5);
	glColor4f(m_outlineColor.r, m_outlineColor.g, m_outlineColor.b, m_outlineColor.a);

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

void CCanvas::FillPoligon(const std::vector<Point>& points)
{
	glColor4f(m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);

	glBegin(GL_POLYGON);
	for (const auto& point : points)
	{
		glVertex2d(point.x, point.y);
	}
	glEnd();
}

void CCanvas::FillEllipse(Point center, double horizontalRadius, double verticalRadius)
{
	glColor4f(m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a);

	double xAngle = 1;
	double yAngle = 0;

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		glVertex2d(xAngle * horizontalRadius + center.x, yAngle * verticalRadius + center.y);
		double t = xAngle;
		xAngle = cos(2 * M_PI / 360) * xAngle - sin(2 * M_PI / 360) * yAngle;
		yAngle = sin(2 * M_PI / 360) * t + cos(2 * M_PI / 360) * yAngle;
	}
	glEnd();
}
