#pragma once
#include <string>

class CStatsValues
{
public:
	void UpdateStats(double data)
	{
		if (m_minValue > data)
		{
			m_minValue = data;
		}
		if (m_maxValue < data)
		{
			m_maxValue = data;
		}
		m_accValue += data;
		++m_countAcc;
	}

	std::string ToString() const
	{
		return "max " + std::to_string(m_maxValue) + ", min " + std::to_string(m_minValue) +
			", avetage " + ((m_accValue != 0) ? std::to_string(m_accValue / m_accValue) : "?") + "\n";
	}

private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};