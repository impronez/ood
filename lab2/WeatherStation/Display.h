#pragma once
#include <iostream>
#include <set>
#include "WeatherData.h"

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(IObservable<SWeatherInfo>& observable)
		: m_observable(observable)
	{}

	~CDisplay()
	{
		m_observable.RemoveObserver(*this);
	}
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	IObservable<SWeatherInfo>& m_observable;
};