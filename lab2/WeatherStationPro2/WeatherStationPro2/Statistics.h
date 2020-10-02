#pragma once
#include "StatsValues.h"
#include "WeatherInfo.h"
#include "DirectionStatsValues.h"
#include <iostream>

class CStatistics
{
public:
	void Update(SWeatherInfo const& data, Event event)
	{
		switch (event)
		{
		case Event::Temperature:
			m_temperatureValues.UpdateStats(data.temperature);
			break;
		case Event::Humidity:
			m_humidityValues.UpdateStats(data.humidity);
			break;
		case Event::Pressure:
			m_pressureValues.UpdateStats(data.pressure);
			break;
		case Event::WindSpeed:
			m_windSpeedValues.UpdateStats(data.windSpeed);
			break;
		case Event::WindDirection:
			m_windDirectionValues.UpdateStats(data.windDirection);
			break;
		}
	}
	std::string ToString(Event event)
	{
		switch (event)
		{
		case Event::Temperature:
			return "Temp: "+ m_temperatureValues.ToString();
		case Event::Humidity:
			return "Humidity: " + m_humidityValues.ToString();
		case Event::Pressure:
			return "Pressure: " + m_pressureValues.ToString();
		case Event::WindSpeed:
			return "Wind Speed: " + m_windSpeedValues.ToString();
		case Event::WindDirection:
			return "Wind Direction: " + m_windDirectionValues.ToString();
		}
		return "";
	}

private:
	CStatsValues m_temperatureValues;
	CStatsValues m_pressureValues;
	CStatsValues m_humidityValues;
	CStatsValues m_windSpeedValues;
	CDirectionStatsValues m_windDirectionValues;
};