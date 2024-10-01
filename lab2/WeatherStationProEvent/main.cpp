#include "WeatherData.h"
#include "StatsDisplay.h"
#include "Display.h"

int main()
{
	CWeatherData weatherData;

	auto statsDisplayPtr = std::make_shared<CStatsDisplay>();
	auto displayPtr = std::make_shared<CDisplay>();

	weatherData.RegisterObserver(statsDisplayPtr, WeatherParameter::TEMPERATURE);
	weatherData.RegisterObserver(displayPtr, WeatherParameter::WIND);

	weatherData.SetMeasurements(25, 0.4, 770, 5, 90);

	displayPtr.reset();

	return 0;
}
