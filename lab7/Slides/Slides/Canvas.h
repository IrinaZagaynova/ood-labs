#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	void SetLineColor(RGBAColor color) override;
	void SetFillColor(RGBAColor color) override;
	void SetLineSize(float lineSize) override;
	void DrawLine(Point from, Point to) override;
	void DrawEllipse(Point center, double horizontalRadius, double verticalRadius) override;
	void FillPoligon(const std::vector<Point>& points) override;
	void FillEllipse(Point center, double horizontalRadius, double verticalRadius) override;

private:
	RGBAColor m_fillColor = { 1, 1, 1, 1 };
	RGBAColor m_outlineColor = { 1, 1, 1, 1 };
	float m_lineWidth = 1;
};