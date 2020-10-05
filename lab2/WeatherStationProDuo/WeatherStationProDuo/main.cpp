#include "WeatherData.h"
#include "WeatherDataPro.h"
#include "StatsDisplay.h"
#include "Display.h"
#include "DisplayPro.h"
#include "StatsDisplayPro.h"

int main()
{
	CWeatherData weatherData;
	CWeatherDataPro weatherDataPro;

	CDisplay displayIndoor;
	CDisplayPro displayOutside;
	weatherData.RegisterObserver(displayIndoor, 1);
	weatherDataPro.RegisterObserver(displayOutside, 1);

	CStatsDisplay statsDisplayIndoor;
	CStatsDisplayPro statsDisplayOutside;
	weatherData.RegisterObserver(statsDisplayIndoor, 2);
	weatherDataPro.RegisterObserver(statsDisplayOutside, 2);

	weatherData.SetMeasurements(3, 0.7, 760);
	weatherDataPro.SetMeasurements(4, 0.8, 761, 2, 180);

	return 0;
}