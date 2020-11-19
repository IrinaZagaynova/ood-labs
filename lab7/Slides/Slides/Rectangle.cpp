#include "Rectangle.h"

CRectangle::CRectangle(Point const& leftTopCorner, double width, double height)
    : m_leftTopCorner(leftTopCorner)
    , m_width(width)
    , m_height(height)
{
}

std::optional<RectD> CRectangle::GetFrame() const
{
    return RectD({ m_leftTopCorner.x,  m_leftTopCorner.y, m_width, m_height});
}

void CRectangle::SetFrame(const RectD& rect)
{
    m_leftTopCorner = { rect.left, rect.top};
    m_width = rect.width;
    m_height = rect.height;
}

void CRectangle::Draw(ICanvas& canvas) const
{
	Point rightTopCorner = { m_leftTopCorner.x + m_width, m_leftTopCorner.y };
	Point leftBottonCorner = { m_leftTopCorner.x, m_leftTopCorner.y - m_height };
	Point rightBottonCorner = { m_leftTopCorner.x + m_width, m_leftTopCorner.y - m_height };

	if (*GetFillStyle()->IsEnabled())
	{
		canvas.SetFillColor(*GetFillStyle()->GetColor());
		canvas.FillPoligon({ m_leftTopCorner, rightTopCorner, rightBottonCorner, leftBottonCorner });
	}

	if (*GetLineStyle()->IsEnabled())
	{
		canvas.SetLineColor(*GetLineStyle()->GetColor());
		canvas.DrawLine(m_leftTopCorner, rightTopCorner);
		canvas.DrawLine(rightTopCorner, rightBottonCorner);
		canvas.DrawLine(rightBottonCorner, leftBottonCorner);
		canvas.DrawLine(leftBottonCorner, m_leftTopCorner);
	}
}
