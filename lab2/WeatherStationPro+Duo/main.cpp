#include "WeatherData.h"
#include "StatsDisplay.h"

int main()
{
	CWeatherData wdIn;
	CWeatherData wdOut;

	CStatsDisplayDuoPro display(&wdIn, &wdOut);
	wdOut.RegisterObserver(display, 2);
	wdIn.RegisterObserver(display, 2);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(4, 0.8, 761, 13, 13);
	wdOut.SetMeasurements(4, 0.8, 761, 5, 280);

	wdIn.RemoveObserver(display);
	wdOut.RemoveObserver(display);

	return 0;
}
