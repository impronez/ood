#pragma once
#include "WeatherData.h"
#include "SensorStats.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:

	void ShowStats(SensorStats stats, std::string sensorName)
	{
		std::cout << "Max " << sensorName << ": " << stats.Max() << std::endl;
		std::cout << "Min " << sensorName << ": " << stats.Min() << std::endl;
		std::cout << "Average " << sensorName << ": " << stats.Average() << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStats.Update(data.temperature);
		m_humidityStats.Update(data.humidity);
		m_pressureStats.Update(data.pressure);

		ShowStats(m_temperatureStats, "Temp");
		ShowStats(m_humidityStats, "Humidity");
		ShowStats(m_pressureStats, "Pressure");
	}

	SensorStats m_temperatureStats;
	SensorStats m_humidityStats;
	SensorStats m_pressureStats;
};