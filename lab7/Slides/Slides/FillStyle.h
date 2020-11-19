#pragma once
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:
	CFillStyle()
		: m_color(RGBAColor(0, 0, 0, 1))
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

private:
	bool m_isEnabled = false;
	RGBAColor m_color;
};