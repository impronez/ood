#pragma once
#include "Observer.h"

enum class WeatherParameter
{
	TEMPERATURE,
	HUMIDITY,
	PRESSURE,
	WIND
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windDirection = 0;
};

class CWeatherData : public CObservable<SWeatherInfo, WeatherParameter>
{
public:
	
	double GetTemperature() const
	{
		return m_temperature;
	}
	
	double GetHumidity() const
	{
		return m_humidity;
	}
	
	double GetPressure() const
	{
		return m_pressure;
	}

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	double GetWindDirection() const
	{
		return m_windDirection;
	}

	void MeasurementsChanged(WeatherParameter param)
	{
		NotifyObservers(param);
	}

	void SetTemperature(double temperature)
	{
		m_temperature = temperature;

		MeasurementsChanged(WeatherParameter::TEMPERATURE);
	}

	void SetPressure(double pressure)
	{
		m_pressure = pressure;

		MeasurementsChanged(WeatherParameter::PRESSURE);
	}

	void SetHumidity(double humidity)
	{
		m_humidity = humidity;

		MeasurementsChanged(WeatherParameter::HUMIDITY);
	}

	void SetWindParams(double speed, double direction)
	{
		m_windSpeed = speed;
		m_windDirection = direction;

		MeasurementsChanged(WeatherParameter::WIND);
	}

	void SetMeasurements(double temp, double pressure, double humidity, double windSpeed, double windDirection)
	{
		m_temperature = temp;
		m_pressure = pressure;
		m_humidity = humidity;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged(WeatherParameter::TEMPERATURE);
		MeasurementsChanged(WeatherParameter::HUMIDITY);
		MeasurementsChanged(WeatherParameter::PRESSURE);
		MeasurementsChanged(WeatherParameter::WIND);
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	double m_windDirection = 0;
};