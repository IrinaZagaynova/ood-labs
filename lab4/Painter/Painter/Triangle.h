#pragma once
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(SPoint const& vertex1, SPoint const& vertex2, SPoint const& vertex3, Color color);

	void Draw(ICanvas& canvas) const override;

	SPoint GetVertex1() const;
	SPoint GetVertex2() const;
	SPoint GetVertex3() const;

private:
	SPoint m_vertex1, m_vertex2, m_vertex3;
};