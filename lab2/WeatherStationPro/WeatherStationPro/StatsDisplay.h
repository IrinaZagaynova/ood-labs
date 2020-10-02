#pragma once
#include "WeatherData.h"
#include "StatsValues.h"
#include "Statistics.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		m_stats.Update(data);
		std::cout << m_stats.ToString();
	}

	CStatistics m_stats;
};