#include "Triangle.h"
#include <algorithm>

CTriangle::CTriangle(Point const& vertex1, Point const& vertex2, Point const& vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

std::optional<RectD> CTriangle::GetFrame() const
{
	double minX = std::min({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	double maxX = std::max({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	double minY = std::min({ m_vertex1.y, m_vertex2.y, m_vertex3.y });
	double maxY = std::max({ m_vertex1.y, m_vertex2.y, m_vertex3.y });

	return RectD({ minX, maxY, maxX - minX, maxY - minY });
}

void CTriangle::SetFrame(const RectD& rect)
{
	RectD frame = *GetFrame();

	RecalculateVertexCoordinates(m_vertex1, rect, frame);
	RecalculateVertexCoordinates(m_vertex2, rect, frame);
	RecalculateVertexCoordinates(m_vertex3, rect, frame);
}

void CTriangle::Draw(ICanvas& canvas) const
{
	if (*GetFillStyle()->IsEnabled())
	{
		canvas.SetFillColor(*GetFillStyle()->GetColor());
		std::vector<Point> points = { m_vertex1, m_vertex2, m_vertex3 };
		canvas.FillPoligon(points);
	}

	if (*GetLineStyle()->IsEnabled())
	{
		canvas.SetLineColor(*GetLineStyle()->GetColor());
		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}
}

void CTriangle::RecalculateVertexCoordinates(Point& vertex, const RectD& rect, const RectD& frame)
{
	vertex.x = rect.left - (frame.left - vertex.x) * rect.width / frame.width;
	vertex.y = rect.top - (frame.top - vertex.y) * rect.height / frame.height;
}


