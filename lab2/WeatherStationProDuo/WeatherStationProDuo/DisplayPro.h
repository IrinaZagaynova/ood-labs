#pragma once
#include "IObserver.h"
#include "WeatherInfoPro.h"
#include <iostream>

class CDisplayPro : public IObserver<SWeatherInfoPro>
{
private:
	void Update(SWeatherInfoPro const& data) override
	{
		std::cout << "Outside data" << std::endl;
		std::cout << "Current Temp: " << data.temperature << std::endl;
		std::cout << "Current Hum: " << data.humidity << std::endl;
		std::cout << "Current Pressure: " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};