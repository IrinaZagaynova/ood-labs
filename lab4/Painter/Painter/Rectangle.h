#pragma once
#include "Shape.h"
#include "Point.h"

class CRectangle : public CShape
{
public:
	CRectangle(SPoint const& leftTopCorner, double width, double height, Color color);
	
	void Draw(ICanvas& canvas) const override;

	SPoint GetLeftTopCorner() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	SPoint m_leftTopCorner;
	double m_width, m_height;
};