#pragma once
#include "CommonTypes.h"
#include <vector>

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetFillColor(RGBAColor color) = 0;
	virtual void SetLineSize(float lineSize) = 0;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void DrawEllipse(Point center, double width, double height) = 0;
	virtual void FillPoligon(const std::vector<Point>& points) = 0;
	virtual void FillEllipse(Point center, double width, double height) = 0;

	virtual ~ICanvas() {};
};