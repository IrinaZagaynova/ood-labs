#pragma once
#include "../Slides/ICanvas.h"

class CMockCanvas : public ICanvas
{
public:
	CMockCanvas(std::ostream& strm)
		: m_strm(strm)
	{
	}

	void SetLineColor(RGBAColor color) override
	{
		m_strm << "line color: " << color.r << " " << color.g << " " << color.b << " " << color.a << "\n";
	}

	void SetFillColor(RGBAColor color) override
	{
		m_strm << "fill color: " << color.r << " " << color.g << " " << color.b << " " << color.a << "\n";
	}

	void SetLineSize(float lineSize) override
	{
		m_strm << "line size: " << lineSize << "\n";
	}

	void DrawLine(Point from, Point to) override
	{
		m_strm << "drawing line\n";
	}

	void DrawEllipse(Point center, double horizontalRadius, double verticalRadius) override
	{
		m_strm << "drawing ellipse\n";
	}

	void FillPoligon(const std::vector<Point>& points) override
	{
		m_strm << "filling poligon\n";
	}

	void FillEllipse(Point center, double horizontalRadius, double verticalRadius) override
	{
		m_strm << "filling ellipse\n";
	}

private:
	std::ostream& m_strm;
};
