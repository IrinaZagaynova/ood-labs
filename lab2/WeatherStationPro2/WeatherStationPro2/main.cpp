#include "WeatherData.h"
#include "StatsDisplay.h"
#include "Display.h"
#include "Event.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 2, { Event::Pressure, Event::Humidity });
	wd.RegisterObserver(display, 2, { Event::Pressure, Event::Humidity });

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1, { Event::Temperature, Event::Humidity });
	
	wd.SetMeasurements(3, 0.7, 750, 2, 270);
	std::cout << "----------------" << std::endl;

	wd.SubscribeToEvent(display, Event::Temperature);
	wd.UnsubscribeFromEvent(statsDisplay, Event::Humidity);

	wd.SetMeasurements(10, 0.8, 760, 2, 270);

	std::cout << "----------------" << std::endl;
	wd.RemoveObserver(display);
	wd.SetMeasurements(3, 0.7, 750, 2, 270);

	return 0;
}