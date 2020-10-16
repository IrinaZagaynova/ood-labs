#pragma once
#include "Shape.h"
#include <vector>

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(SPoint center, size_t vertexCount, double radius, Color color);

	void Draw(ICanvas& canvas) const override;
	std::vector<SPoint> GetVertices() const;

	SPoint GetCenter() const;
	double GetVertexCount() const;
	double GetRadius() const;

private:
	SPoint m_center;
	size_t m_vertexCount;
	double m_radius;
};