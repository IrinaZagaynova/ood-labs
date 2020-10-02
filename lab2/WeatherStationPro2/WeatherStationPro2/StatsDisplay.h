#pragma once
#include "WeatherData.h"
#include "StatsValues.h"
#include "Statistics.h"

class CStatsDisplay : public IObserver<SWeatherInfo, Event>
{
private:
	void Update(SWeatherInfo const& data, const Event& event) override
	{
		m_stats.Update(data, event);
		std::cout << m_stats.ToString(event);
	}

	CStatistics m_stats;
};