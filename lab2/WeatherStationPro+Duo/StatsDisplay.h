#pragma once
#include "WeatherData.h"
#include "CStats.h"
#include <iostream>
#include <string>

class CStatsDisplayDuoPro : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplayDuoPro(CObservable<SWeatherInfo>* weatherInfoIn, CObservable<SWeatherInfo>* weatherInfoOut)
		: m_weatherInfoIn(weatherInfoIn),
		m_weatherInfoOut(weatherInfoOut)
	{}
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
		std::cout << "----------------" << std::endl;
	}

	void Update(SWeatherInfo const& data, const CObservable<SWeatherInfo>* observable) override
	{
		std::string location = observable == m_weatherInfoIn ? "Inside"
			: observable == m_weatherInfoOut ? "Outside"
			: "Undefined";

		m_temperatureStats.Update(data.temperature);
		m_humidityStats.Update(data.humidity);
		m_pressureStats.Update(data.pressure);

		std::cout << "Location: " << location << std::endl;
		ShowStats(m_temperatureStats, "Temp");
		ShowStats(m_humidityStats, "Humidity");
		ShowStats(m_pressureStats, "Pressure");

		if (observable == m_weatherInfoOut)
		{
			m_windStats.Update(data.windSpeed, data.windDirection);
			ShowWindStats(m_windStats);
		}		
	}

	CStats m_temperatureStats;
	CStats m_humidityStats;
	CStats m_pressureStats;
	CWindStats m_windStats;

	const CObservable<SWeatherInfo>* m_weatherInfoIn;
	const CObservable<SWeatherInfo>* m_weatherInfoOut;
};