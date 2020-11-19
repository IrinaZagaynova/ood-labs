#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(Point center, double horizontalRadius, double verticalRadius);

	std::optional<RectD> GetFrame()const override;
	void SetFrame(const RectD& rect) override;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};