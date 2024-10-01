#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../WeatherData.h"
#include "../Display.h"

class CTestDisplayDuo : public CDisplayDuo
{
public:
	CTestDisplayDuo(CObservable<SWeatherInfo>* weatherInfoIn, CObservable<SWeatherInfo>* weatherInfoOut)
		: CDisplayDuo(weatherInfoIn, weatherInfoOut),
		m_weatherInfoIn(weatherInfoIn),
		m_weatherInfoOut(weatherInfoOut)
	{}


	std::string locationOfLastSensor;
private:
	void Update(SWeatherInfo const& data, const CObservable<SWeatherInfo>* observable) override
	{
		locationOfLastSensor = observable == m_weatherInfoIn ? "Inside"
			: observable == m_weatherInfoOut ? "Outside"
			: "Undefined";
	}

	CObservable<SWeatherInfo>* m_weatherInfoIn;
	CObservable<SWeatherInfo>* m_weatherInfoOut;
};

TEST_CASE("check display duo")
{
	CWeatherData wdIn;
	CWeatherData wdOut;

	auto displayPtr = std::make_shared<CTestDisplayDuo>(CTestDisplayDuo(&wdIn, &wdOut));

	wdIn.RegisterObserver(displayPtr, 1);
	wdOut.RegisterObserver(displayPtr, 1);

	wdIn.SetMeasurements(0, 0, 770);
	REQUIRE(displayPtr.get()->locationOfLastSensor == "Inside");

	wdOut.SetMeasurements(1, 1, 771);
	REQUIRE(displayPtr.get()->locationOfLastSensor == "Outside");


	wdIn.RemoveObserver(displayPtr);
	wdOut.RemoveObserver(displayPtr);
}