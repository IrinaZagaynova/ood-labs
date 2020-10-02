#pragma once
#include "StatsValues.h"
#include "WeatherInfo.h"
#include <iostream>

class CStatistics
{
public:
	void Update(SWeatherInfo const& data)
	{
		m_temperatureValues.UpdateStats(data.temperature);
		m_pressureValues.UpdateStats(data.pressure);
		m_humidityValues.UpdateStats(data.humidity);
	}
	void Print()
	{
		std::cout << "Temp: " << m_temperatureValues.ToString();
		std::cout << "Pressure: " << m_pressureValues.ToString();
		std::cout << "Humidity: " << m_humidityValues.ToString();
		std::cout << "----------------" << std::endl;
	}
private:
	CStatsValues m_temperatureValues;
	CStatsValues m_pressureValues;
	CStatsValues m_humidityValues;
};