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
	void Print(Event event)
	{
		switch (event)
		{
		case Event::Temperature:
			std::cout << "Temp: " << m_temperatureValues.ToString();
			break;
		case Event::Humidity:
			std::cout << "Humidity: " << m_humidityValues.ToString();
			break;
		case Event::Pressure:
			std::cout << "Pressure: " << m_pressureValues.ToString();
			break;
		case Event::WindSpeed:
			std::cout << "Wind Speed: " << m_windSpeedValues.ToString();
			break;
		case Event::WindDirection:
			std::cout << "Wind Direction: " << m_windDirectionValues.ToString();
			break;
		}
	}
private:
	CStatsValues m_temperatureValues;
	CStatsValues m_pressureValues;
	CStatsValues m_humidityValues;
	CStatsValues m_windSpeedValues;
	CDirectionStatsValues m_windDirectionValues;
};