#pragma once
#include "ICanvas.h"
#include <vector>

class RGBcolor
{
public:
	RGBcolor(double red, double green, double blue)
		: m_red(GLdouble(red)), m_green(GLdouble(green)), m_blue(GLdouble(blue))
	{
	}

	std::vector<GLdouble> GetRGBColor()
	{
		return { m_red, m_green, m_blue };
	}

private:
	GLdouble m_red;
	GLdouble m_green;
	GLdouble m_blue;
};

class CCanvas : public ICanvas
{
public:
	CCanvas() = default;
	void SetColor(Color color) override;
	void DrawLine(SPoint from, SPoint to) override;
	void DrawEllipse(SPoint center, double width, double height) override;

private:
	RGBcolor m_color = { GLdouble(1), GLdouble(0), GLdouble(0) };
};