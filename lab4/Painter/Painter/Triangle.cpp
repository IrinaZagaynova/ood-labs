#include "Triangle.h"

CTriangle::CTriangle(SPoint const& vertex1, SPoint const& vertex2, SPoint const& vertex3, Color color)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CShape(color)
{
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

SPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

SPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

SPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
