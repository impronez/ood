#pragma once
#include <iostream>
#include "WeatherData.h"

class CDisplay : public IObserver<SWeatherInfo, WeatherParameter>
{
private:
	void Update(SWeatherInfo const& data, WeatherParameter param) override
	{
		switch (param)
		{
		case WeatherParameter::TEMPERATURE:
			std::cout << "Current Temp " << data.temperature << std::endl;
			break;
		case WeatherParameter::HUMIDITY:
			std::cout << "Current Hum " << data.humidity << std::endl;
			break;
		case WeatherParameter::PRESSURE:
			std::cout << "Current Pressure " << data.pressure << std::endl;
			break;
		case WeatherParameter::WIND:
			std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
			std::cout << "Current Wind Direction " << data.windDirection << std::endl;
			break;
		default:
			break;
		}

		std::cout << "----------------" << std::endl;
	}
};