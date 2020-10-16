#pragma once
#include "Point.h"
#include "Color.h"

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(SPoint from, SPoint to) = 0;
	virtual void DrawEllipse(SPoint leftTop, double width, double height) = 0;
};