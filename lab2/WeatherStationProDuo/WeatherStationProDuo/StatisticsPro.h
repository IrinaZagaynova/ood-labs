#pragma once
#include "StatsValues.h"
#include "WeatherInfoPro.h"
#include "DirectionStatsValues.h"
#include <iostream>

class CStatisticsPro
{
public:
	void Update(SWeatherInfoPro const& data)
	{
		m_temperatureValues.UpdateStats(data.temperature);
		m_pressureValues.UpdateStats(data.pressure);
		m_humidityValues.UpdateStats(data.humidity);
		m_windSpeedValues.UpdateStats(data.windSpeed);
		m_windDirectionValues.UpdateStats(data.windDirection);
	}
	void Print()
	{
		std::cout << "Temp: " << m_temperatureValues.ToString();
		std::cout << "Pressure: " << m_pressureValues.ToString();
		std::cout << "Humidity: " << m_humidityValues.ToString();
		std::cout << "Wind Speed: " << m_windSpeedValues.ToString();
		std::cout << "Wind Direction: " << m_windDirectionValues.ToString();
		std::cout << "----------------" << std::endl;
	}
private:
	CStatsValues m_temperatureValues;
	CStatsValues m_pressureValues;
	CStatsValues m_humidityValues;
	CStatsValues m_windSpeedValues;
	CDirectionStatsValues m_windDirectionValues;
};