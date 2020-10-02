#pragma once
#include "WeatherData.h"
#include "StatsValues.h"
#include "Statistics.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data, const Event& event) override
	{
		m_stats.Update(data, event);
		m_stats.Print(event);
	}

	CStatistics m_stats;
};