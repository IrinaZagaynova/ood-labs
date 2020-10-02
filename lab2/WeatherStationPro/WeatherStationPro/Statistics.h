#pragma once
#include "StatsValues.h"
#include "WeatherInfo.h"
#include "DirectionStatsValues.h"
#include <iostream>

class CStatistics
{
public:
	void Update(SWeatherInfo const& data)
	{
		m_temperatureValues.UpdateStats(data.temperature);
		m_pressureValues.UpdateStats(data.pressure);
		m_humidityValues.UpdateStats(data.humidity);
		m_windSpeedValues.UpdateStats(data.windSpeed);
		m_windDirectionValues.UpdateStats(data.windDirection);
	}

	std::string ToString()
	{
		return "Temp: " + m_temperatureValues.ToString()
			+ "Pressure: " + m_pressureValues.ToString()
			+ "Humidity: " + m_humidityValues.ToString() 
			+ "Wind Speed: " + m_windSpeedValues.ToString() 
			+ "Wind Direction: " + m_windDirectionValues.ToString()
			+ "----------------" + "\n";
	}
private:
	CStatsValues m_temperatureValues;
	CStatsValues m_pressureValues;
	CStatsValues m_humidityValues;
	CStatsValues m_windSpeedValues;
	CDirectionStatsValues m_windDirectionValues;
};