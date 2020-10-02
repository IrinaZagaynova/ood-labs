#include "WeatherData.h"
#include "StatsDisplay.h"
#include "Display.h"

int main()
{
	CWeatherData wd1(StationType::In);
	CWeatherData wd2(StationType::Out);

	CDisplay display;
	wd1.RegisterObserver(display, 1);
	wd2.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay;
	wd1.RegisterObserver(statsDisplay, 2);
	wd2.RegisterObserver(statsDisplay, 2);

	wd1.SetMeasurements(3, 0.7, 760);
	wd2.SetMeasurements(4, 0.8, 761);

	return 0;
}