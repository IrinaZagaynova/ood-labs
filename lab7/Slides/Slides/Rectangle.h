#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(Point const& leftTopCorner, double width, double height);

	std::optional<RectD> GetFrame()const override;
	void SetFrame(const RectD& rect) override;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_leftTopCorner;
	double m_width;
	double m_height;
};
