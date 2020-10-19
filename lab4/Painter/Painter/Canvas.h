#pragma once
#include "ICanvas.h"
#include <vector>

class CCanvas : public ICanvas
{
public:

	struct RGBcolor
	{
		RGBcolor(double red, double green, double blue)
			: red(GLdouble(red)), green(GLdouble(green)), blue(GLdouble(blue))
		{
		}

		GLdouble red, green, blue;
	};

	CCanvas() = default;
	void SetColor(Color color) override;
	void DrawLine(SPoint from, SPoint to) override;
	void DrawEllipse(SPoint center, double width, double height) override;

private:
	RGBcolor m_color = RGBcolor(1, 0, 0);
};