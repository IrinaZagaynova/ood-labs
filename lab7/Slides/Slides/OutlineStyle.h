#pragma once
#include "IOutlineStyle.h"

class COutlineStyle : public IOutlineStyle
{
public:
	COutlineStyle()
		: m_color(RGBAColor(0, 0, 0, 1))
		, m_lineWidth(1)
	{
	}

	std::optional<bool> IsEnabled()const override
	{
		return m_isEnabled;
	}

	void Enable(bool enable) override
	{
		m_isEnabled = enable;
	}

	std::optional<RGBAColor> GetColor()const override
	{
		return m_color;
	}

	void SetColor(const RGBAColor color) override
	{
		m_color = color;
	}

	std::optional<float> GetLineWidth()const override
	{
		return m_lineWidth;
	}

	void SetLineWidth(float lineWidth) override
	{
		m_lineWidth = lineWidth;
	}

private:
	bool m_isEnabled = false;
	RGBAColor m_color;
	float m_lineWidth;
};