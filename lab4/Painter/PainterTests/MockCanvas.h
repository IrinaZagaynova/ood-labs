#pragma once
#include "../Painter/ICanvas.h"
#include <sstream>

class MockCanvas : public ICanvas
{
public:
	MockCanvas(std::ostream& strm)
		: m_strm(strm)
	{
	}
	void SetColor(Color color) override
	{
		m_color = color;
		m_strm << "color is " << ColorToString(m_color) << "\n";
	}
	void DrawLine(SPoint from, SPoint to) override
	{
		m_strm << "draw a line from " << from.x << " " << from.y << " to " << to.x << " " << to.y << "\n";
	}
	void DrawEllipse(SPoint center, double width, double height) override
	{
		m_strm << "draw an ellipse centered at " << center.x << " " << center.y
			<< ", a width of " << width << ", a height of " << height << "\n";
	}

private:
	std::string ColorToString(Color color)
	{
		for (auto iter = COLORS_NAMES.begin(); iter != COLORS_NAMES.end(); iter++)
		{
			if (iter->second == color)
			{
				return iter->first;
			}
		}
		return "";
	}

private:
	Color m_color = Color::Black;
	std::ostream& m_strm;
};