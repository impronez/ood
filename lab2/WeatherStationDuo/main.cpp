#include "WeatherData.h"
#include "Display.h"

int main()
{
	CWeatherData wdIn;
	CWeatherData wdOut;

	auto displayPtr = std::make_shared<CDisplayDuo>(CDisplayDuo(&wdIn, &wdOut));
	wdOut.RegisterObserver(displayPtr, 2);
	wdIn.RegisterObserver(displayPtr, 2);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(4, 0.8, 761);

	wdIn.RemoveObserver(displayPtr);
	wdOut.RemoveObserver(displayPtr);

	return 0;
}
