#include "Rectangle.h"

CRectangle::CRectangle(SPoint const& leftTopCorner, double width, double height, Color color)
	: m_leftTopCorner(leftTopCorner)
	, m_width(width)
	, m_height(height)
	, CShape(color)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	SPoint rightTopCorner = { m_leftTopCorner.x + m_width, m_leftTopCorner.y };
	SPoint leftBottonCorner = { m_leftTopCorner.x, m_leftTopCorner.y - m_height };
	SPoint rightBottonCorner = { m_leftTopCorner.x + m_width, m_leftTopCorner.y - m_height };

	canvas.SetColor(GetColor());
	canvas.DrawLine(m_leftTopCorner, rightTopCorner);
	canvas.DrawLine(rightTopCorner, rightBottonCorner);
	canvas.DrawLine(rightBottonCorner, leftBottonCorner);
	canvas.DrawLine(leftBottonCorner, m_leftTopCorner);
}

SPoint CRectangle::GetLeftTopCorner() const
{
	return m_leftTopCorner;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}