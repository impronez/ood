#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../WeatherData.h"
#include "../Display.h"

class CTestDisplayDuo : public CDisplayDuo
{
public:
	CTestDisplayDuo(CObservable<SWeatherInfo>* weatherInfoIn, CObservable<SWeatherInfo>* weatherInfoOut)
		: CDisplayDuo(weatherInfoIn, weatherInfoOut)
	{}

	Location locationOfLastSensor;
private:
	void Update(SWeatherInfo const& data) override
	{
		locationOfLastSensor = data.location;
	}
};

TEST_CASE("check display duo")
{
	CWeatherData wdIn(Location::Inside);
	CWeatherData wdOut(Location::Outside);

	CTestDisplayDuo display(&wdIn, &wdOut);

	wdIn.RegisterObserver(display, 1);
	wdOut.RegisterObserver(display, 1);

	wdIn.SetMeasurements(0, 0, 770);
	REQUIRE(display.locationOfLastSensor == wdIn.GetLocation());

	wdOut.SetMeasurements(1, 1, 771);
	REQUIRE(display.locationOfLastSensor == wdOut.GetLocation());

	wdIn.RemoveObserver(display);
	wdOut.RemoveObserver(display);
}