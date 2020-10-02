#pragma once
#include "WeatherInfo.h"
#include "WeatherInfoPro.h"
#include "StatsValues.h"
#include "Statistics.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		m_stats.Update(data);
		std::cout << "Indoor Statistics" << std::endl;
		std::cout << m_stats.ToString();
	}
private:
	CStatistics m_stats;
};