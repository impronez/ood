#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../Observer.h"
#include "../WeatherData.h"

class CTestDisplay : public IObserver<SWeatherInfo>
{
public:

	typedef IObservable<SWeatherInfo> ObservableType;

	CTestDisplay(ObservableType& observable)
		: m_observable(observable) {}
private:

	void Update(SWeatherInfo const& data) override
	{
		m_observable.RemoveObserver(std::make_shared<CTestDisplay>(*this));

		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
	ObservableType& m_observable;
};

class CPriorityDisplay : public IObserver<SWeatherInfo>
{
public:

	typedef IObservable<SWeatherInfo> ObservableType;

	CPriorityDisplay(ObservableType& observable, int priority)
		: m_observable(observable),
		m_priority(priority)
	{}
private:

	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Priority " << m_priority << std::endl;
	}
	ObservableType& m_observable;

	int m_priority;
};

TEST_CASE("test with deleting observer")
{
	CWeatherData weatherData;
	auto testDisplayPtr = std::make_shared<CTestDisplay>(CTestDisplay(weatherData));

	weatherData.RegisterObserver(testDisplayPtr, 1);
	weatherData.SetMeasurements(0, 0, 770);

	REQUIRE_NOTHROW(weatherData.SetMeasurements(1, 1, 780));
}

TEST_CASE("test with priority")
{
	CWeatherData weatherData;
	auto firstDisplay = std::make_shared<CPriorityDisplay>(CPriorityDisplay(weatherData, 11));
	auto secondDisplay = std::make_shared<CPriorityDisplay>(CPriorityDisplay(weatherData, 2));
	auto thirdDisplay = std::make_shared<CPriorityDisplay>(CPriorityDisplay(weatherData, 3));

	weatherData.RegisterObserver(secondDisplay, 2);
	weatherData.RegisterObserver(thirdDisplay, 3);
	weatherData.RegisterObserver(firstDisplay, 11);

	weatherData.SetMeasurements(1, 1, 771);
}