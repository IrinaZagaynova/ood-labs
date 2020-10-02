#include "WeatherData.h"
#include "StatsDisplay.h"
#include "Display.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 2);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1);

	wd.SetMeasurements(3, 0.7, 760, 2, 270);
	wd.SetMeasurements(4, 0.8, 761, 4, 180);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, 1, 360);
	wd.SetMeasurements(-10, 0.8, 761, 2, 0);

	return 0;
}