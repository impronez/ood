#pragma once
#include <iostream>
#include "WeatherData.h"

namespace
{
	const std::string INSIDE = "Inside";
	const std::string OUTSIDE = "Outside";
	const std::string UNDEFINED = "Undefined";
}

class CDisplayDuo : public IObserver<SWeatherInfo>
{
public:
	CDisplayDuo(CObservable<SWeatherInfo>* weatherInfoIn, CObservable<SWeatherInfo>* weatherInfoOut)
		: m_weatherInfoIn(weatherInfoIn),
		m_weatherInfoOut(weatherInfoOut	)
	{}
private:
	void Update(SWeatherInfo const& data, const CObservable<SWeatherInfo>* observable) override
	{
		std::string location = observable == m_weatherInfoIn ? INSIDE
			: observable == m_weatherInfoOut ? OUTSIDE
			: UNDEFINED;

		std::cout << "Current Location " << location << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;

		if (observable == m_weatherInfoOut)
		{
			std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
			std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		}

		std::cout << "----------------" << std::endl;
	}

	const CObservable<SWeatherInfo>* m_weatherInfoIn;
	const CObservable<SWeatherInfo>* m_weatherInfoOut;
};