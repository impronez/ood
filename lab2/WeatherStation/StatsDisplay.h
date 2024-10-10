#pragma once
#include "WeatherData.h"
#include "SensorStats.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(IObservable<SWeatherInfo>& observable)
		: m_observable(observable)
	{}
	~CStatsDisplay()
	{
		m_observable.RemoveObserver(*this);
	}
private:

	void ShowStats(SensorStats stats, std::string sensorName)
	{
		std::cout << "Max " << sensorName << ": " << stats.GetMax() << std::endl;
		std::cout << "Min " << sensorName << ": " << stats.GetMin() << std::endl;
		std::cout << "Average " << sensorName << ": " << stats.GetAverage() << std::endl;
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

	IObservable<SWeatherInfo>& m_observable;
};