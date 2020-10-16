#include "RegularPolygon.h"
#define _USE_MATH_DEFINES
#include <math.h>

CRegularPolygon::CRegularPolygon(SPoint center, size_t vertexCount, double radius, Color color)
	: m_center(center)
    , m_vertexCount(vertexCount)
    , m_radius(radius)
    , CShape(color)
{
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
    std::vector<SPoint> vertices = GetVertices();

    canvas.SetColor(GetColor());
    for (size_t i = 0; i < m_vertexCount - 1; i++)
    {
        canvas.DrawLine(vertices[i], vertices[i + 1]);
    }
    canvas.DrawLine(vertices[0], vertices[m_vertexCount - 1]);
}

std::vector<SPoint> CRegularPolygon::GetVertices() const
{
    std::vector<SPoint> vertices;
    double angle = 2 * M_PI / m_vertexCount;

    for (size_t i = 0; i < m_vertexCount; i++)
    {
        vertices.push_back( 
            { m_center.x + m_radius * cos(angle * double(i)),
            m_center.y + m_radius * sin(angle * double(i)) }
        );
    }

    return vertices;
}

SPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}

