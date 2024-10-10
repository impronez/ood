#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"
#include <memory>

int main()
{
	CWeatherData wd;

	CDisplay display(wd);
	wd.RegisterObserver(display, 2);

	CStatsDisplay statsDisplay(wd);
	wd.RegisterObserver(statsDisplay, 2);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);

	wd.RemoveObserver(display);

	return 0;
}