#include "Ellipse.h"

CEllipse::CEllipse(Point center, double horizontalRadius, double verticalRadius)
    : m_center(center)
    , m_horizontalRadius(horizontalRadius)
    , m_verticalRadius(verticalRadius)
{
}

std::optional<RectD> CEllipse::GetFrame() const
{
	return RectD({ m_center.x - m_horizontalRadius, m_center.y + m_verticalRadius, m_horizontalRadius * 2, m_verticalRadius * 2});
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_verticalRadius = rect.width / 2;
	m_horizontalRadius = rect.height / 2;
	m_center = { rect.left + m_horizontalRadius, rect.top - m_verticalRadius };
}

void CEllipse::Draw(ICanvas& canvas) const
{
	if (*GetFillStyle()->IsEnabled())
	{
		canvas.SetFillColor(*GetFillStyle()->GetColor());
		canvas.FillEllipse(m_center, m_horizontalRadius, m_verticalRadius);
	}

	if (*GetLineStyle()->IsEnabled())
	{
		canvas.SetLineColor(*GetLineStyle()->GetColor());
		canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
	}
}
