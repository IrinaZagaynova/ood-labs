#include "WeatherData.h"
#include "WeatherDataPro.h"
#include "StatsDisplay.h"
#include "Display.h"
#include "DisplayPro.h"
#include "StatsDisplayPro.h"

int main()
{
	CWeatherData wd1;
	CWeatherDataPro wd2;

	CDisplay display1;
	CDisplayPro display2;
	wd1.RegisterObserver(display1, 1);
	wd2.RegisterObserver(display2, 1);

	CStatsDisplay statsDisplay1;
	CStatsDisplayPro statsDisplay2;
	wd1.RegisterObserver(statsDisplay1, 2);
	wd2.RegisterObserver(statsDisplay2, 2);

	wd1.SetMeasurements(3, 0.7, 760);
	wd2.SetMeasurements(4, 0.8, 761, 2, 180);

	return 0;
}