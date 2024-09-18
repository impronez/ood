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
		m_observable.RemoveObserver(*this);

		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
	ObservableType& m_observable;
};

TEST_CASE()
{
	CWeatherData weatherData;
	CTestDisplay testDisplay(weatherData);

	weatherData.RegisterObserver(testDisplay);
	weatherData.SetMeasurements(0, 0, 770);
}