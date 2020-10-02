#pragma once
#include "WeatherInfoPro.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

class CDirectionStatsValues
{
public:
	void UpdateStats(double data)
	{
		m_x += cos(data * M_PI / 180);
		m_y += sin(data * M_PI / 180);
		m_avetageValue = atan2(m_y, m_x) * 180 / M_PI;

		if (m_avetageValue < 0)
		{
			m_avetageValue += 360;
		}
	}

	std::string ToString() const
	{
		return "avetage " + std::to_string(m_avetageValue) + "\n";
	}
private:
	double m_x = 0;
	double m_y = 0;
	double m_avetageValue = 0;
};