#pragma once
#include "Shape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Point const& vertex1, Point const& vertex2, Point const& vertex3);

	std::optional<RectD> GetFrame()const override;
	void SetFrame(const RectD& rect) override;

	void Draw(ICanvas& canvas)const override;

private:
	void RecalculateVertexCoordinates(Point& vertex, const RectD& rect, const RectD& frame);

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};