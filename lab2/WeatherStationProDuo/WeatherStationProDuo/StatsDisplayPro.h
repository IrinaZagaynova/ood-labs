#pragma once
#include "WeatherDataPro.h"
#include "WeatherInfoPro.h"
#include "StatsValues.h"
#include "StatisticsPro.h"

class CStatsDisplayPro : public IObserver<SWeatherInfoPro>
{
private:
	void Update(SWeatherInfoPro const& data) override
	{
		m_stats.Update(data);
		std::cout << "Outside statistics" << std::endl;
		std::cout << m_stats.ToString();
	}
private:
	CStatisticsPro m_stats;
};