#pragma once
#include "IObserver.h"
#include "WeatherInfo.h"
#include <iostream>

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp: " << data.temperature << std::endl;
		std::cout << "Current Hum: " << data.humidity << std::endl;
		std::cout << "Current Pressure: " << data.pressure << std::endl;
		std::cout << "Current Wind Speed : " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction : " << data.windDirection << std::endl;
		std::cout << "----------------" << std::endl;
	}
};