#include "WeatherData.h"
#include "Display.h"

int main()
{
	CWeatherData wdIn(Location::Inside);
	CWeatherData wdOut(Location::Outside);

	CDisplayDuo display(&wdIn, &wdOut);
	wdOut.RegisterObserver(display, 2);
	wdIn.RegisterObserver(display, 2);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(4, 0.8, 761);

	wdIn.RemoveObserver(display);
	wdOut.RemoveObserver(display);

	return 0;
}
