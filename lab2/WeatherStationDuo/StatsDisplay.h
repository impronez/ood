#pragma once
#include "WeatherData.h"
#include "CStats.h"
#include <iostream>
#include <string>

class CStatsDisplayPro : public IObserver<SWeatherInfo>
{
private:
	void ShowStats(SensorStats stats, std::string sensorName)
	{
		std::cout << "Max " << sensorName << ": " << stats.GetMax() << std::endl;
		std::cout << "Min " << sensorName << ": " << stats.GetMin() << std::endl;
		std::cout << "Average " << sensorName << ": " << stats.GetAverage() << std::endl;
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
	}

	SensorStats m_temperatureStats;
	SensorStats m_humidityStats;
	SensorStats m_pressureStats;

	const CObservable<SWeatherInfo>* m_weatherInfoIn;
	const CObservable<SWeatherInfo>* m_weatherInfoOut;
};