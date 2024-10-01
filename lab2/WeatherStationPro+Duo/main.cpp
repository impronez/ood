#include "WeatherData.h"
#include "StatsDisplay.h"

int main()
{
	CWeatherData wdIn;
	CWeatherData wdOut;

	auto displayPtr = std::make_shared<CStatsDisplayDuoPro>(CStatsDisplayDuoPro(&wdIn, &wdOut));
	wdOut.RegisterObserver(displayPtr, 2);
	wdIn.RegisterObserver(displayPtr, 2);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(4, 0.8, 761, 13, 13);
	wdOut.SetMeasurements(4, 0.8, 761, 5, 280);

	wdIn.RemoveObserver(displayPtr);
	wdOut.RemoveObserver(displayPtr);

	return 0;
}
