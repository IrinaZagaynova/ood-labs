#pragma once
#include "Shape.h"

class CEllipse : public CShape
{
public:
	CEllipse(SPoint center, double horizontalRadius, double verticalRadius, Color color);

	void Draw(ICanvas& canvas) const override;

	SPoint GetCenter() const;
	double GetHorizontalRadius() const;
	double GetVerticalRadius() const;

private:
	SPoint m_center;
	double m_horizontalRadius, m_verticalRadius;
};