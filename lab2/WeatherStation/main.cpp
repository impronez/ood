#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"
#include <memory>

int main()
{
	CWeatherData wd;

	auto displayPtr = std::make_shared<CDisplay>(CDisplay());
	wd.RegisterObserver(displayPtr, 2);

	auto statsDisplayPtr = std::make_shared<CStatsDisplay>(CStatsDisplay());
	wd.RegisterObserver(statsDisplayPtr, 2);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplayPtr);
	std::cout << "\nObserver removed!\n\n";

	wd.SetMeasurements(10, 0.8, 761);

	wd.RemoveObserver(displayPtr);
	return 0;
}