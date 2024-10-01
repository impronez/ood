#pragma once
#include "WeatherData.h"
#include "CStats.h"
#include <iostream>
#include <string>

class CStatsDisplay : public IObserver<SWeatherInfo, WeatherParameter>
{
private:
	void ShowStats(const CStats& stats, const std::string sensorName) const
	{
		std::cout << "Max " << sensorName << ": " << stats.GetMax() << std::endl;
		std::cout << "Min " << sensorName << ": " << stats.GetMin() << std::endl;
		std::cout << "Average " << sensorName << ": " << stats.GetAverage() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void ShowWindStats(const CWindStats& stats) const
	{
		std::cout << "Max Wind Speed: " << stats.GetMaxSpeed() << std::endl;
		std::cout << "Min Wind Speed: " << stats.GetMinSpeed() << std::endl;
		std::cout << "Average Wind Speed: " << stats.GetAverageSpeed() << std::endl;
		std::cout << "Average Wind Direction: " << stats.GetAverageDirection() << std::endl;
	}

	void Update(SWeatherInfo const& data, WeatherParameter param) override
	{
		switch (param)
		{
		case WeatherParameter::TEMPERATURE:
			m_temperatureStats.Update(data.temperature);
			ShowStats(m_temperatureStats, "Temp");
			break;
		case WeatherParameter::HUMIDITY:
			m_humidityStats.Update(data.humidity);
			ShowStats(m_humidityStats, "Humidity");
			break;
		case WeatherParameter::PRESSURE:
			m_pressureStats.Update(data.pressure);
			ShowStats(m_pressureStats, "Pressure");
			break;
		case WeatherParameter::WIND:
			m_windStats.Update(data.windSpeed, data.windDirection);
			ShowWindStats(m_windStats);
			break;
		default:
			break;
		}		
	}

	CStats m_temperatureStats;
	CStats m_humidityStats;
	CStats m_pressureStats;
	CWindStats m_windStats;
};