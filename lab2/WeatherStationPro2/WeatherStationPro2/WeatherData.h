#pragma once
#include <iostream>
#include "Observable.h"
#include "WeatherInfo.h"

class CWeatherData : public CObservable<SWeatherInfo>
{
public:

	double GetTemperature()const
	{
		return m_temperature;
	}

	double GetHumidity()const
	{
		return m_humidity;
	}

	double GetPressure()const
	{
		return m_pressure;
	}

	double GetWindSpeed()const
	{
		return m_windSpeed;
	}

	double GetWindDitection()const
	{
		return m_windDirection;
	}

	void MeasurementsChanged(const std::set<Event>& changedEvents)
	{
		NotifyObservers(changedEvents);
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windDirection)
	{
		std::set<Event> changedEvents;
		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			changedEvents.insert(Event::Humidity);
		}

		if (m_temperature != temp)
		{
			m_temperature = temp;
			changedEvents.insert(Event::Temperature);
		}

		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			changedEvents.insert(Event::Pressure);
		}

		if (m_windSpeed != windSpeed)
		{
			m_windSpeed = windSpeed;
			changedEvents.insert(Event::WindSpeed);
		}

		if (m_windDirection != windDirection)
		{
			m_windDirection = windDirection;
			changedEvents.insert(Event::WindDirection);
		}

		MeasurementsChanged(changedEvents);
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDitection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	double m_windDirection = 0;
};