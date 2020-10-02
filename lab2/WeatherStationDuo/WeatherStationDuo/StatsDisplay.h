#pragma once
#include "WeatherData.h"
#include "WeatherInfo.h"
#include "StatsValues.h"
#include "Statistics.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		if (data.type == StationType::In)
		{
			m_inStats.Update(data);
			std::cout << "Indoor Statistics" << std::endl;
			std::cout << m_inStats.ToString();
		}
		else if (data.type == StationType::Out)
		{
			m_outStats.Update(data);
			std::cout << "Outside statistics" << std::endl;
			std::cout << m_outStats.ToString();
		}
	}
private:
	CStatistics m_inStats;
	CStatistics m_outStats;
};