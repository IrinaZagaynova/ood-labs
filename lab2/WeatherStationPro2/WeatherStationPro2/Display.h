#pragma once
#include "IObserver.h"
#include "WeatherInfo.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo, Event>
{
private:
	void Update(SWeatherInfo const& data, const Event& event) override
	{
		switch (event)
		{
		case Event::Temperature:
			std::cout << "Current Temp: " << data.temperature << std::endl;
			break;
		case Event::Humidity:
			std::cout << "Current Hum: " << data.humidity << std::endl;
			break;
		case Event::Pressure:
			std::cout << "Current Pressure: " << data.pressure << std::endl;
			break;
		case Event::WindSpeed:
			std::cout << "Current Wind Speed : " << data.windSpeed << std::endl;
			break;
		case Event::WindDirection:
			std::cout << "Current Wind Direction : " << data.windDirection << std::endl;
			break;
		}
	}
};