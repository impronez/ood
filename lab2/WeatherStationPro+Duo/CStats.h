#pragma once
#include <cmath>
#include <numbers>
#include <climits>

class CWindStats
{
public:
	void Update(double speed, double direction)
	{
		if (m_minSpeed > speed)
		{
			m_minSpeed = speed;
		}
		if (m_maxSpeed < speed)
		{
			m_maxSpeed = speed;
		}
		m_totalSpeed += speed;

		double radianDirection = direction * std::numbers::pi / 180.0;

		double x = speed * cos(radianDirection);
		double y = speed * sin(radianDirection);

		m_sumX += x;
		m_sumY += y;
		++m_count;
	}

	double GetMinSpeed() const 
	{
		return m_minSpeed;
	}

	double GetMaxSpeed() const
	{
		return m_maxSpeed;
	}

	double GetAverageSpeed() const 
	{
		if (m_count == 0)
		{
			return 0;
		}

		return m_totalSpeed / m_count;
	}

	double GetAverageDirection() const
	{
		if (m_count == 0)
		{
			return 0;
		}

		double averageDirection = atan2(m_sumY / m_count, m_sumX / m_count) * 180.0 / std::numbers::pi;
		return fmod(averageDirection + 360.0, 360.0);
	}

private:
	double m_minSpeed = std::numeric_limits<double>::infinity();
	double m_maxSpeed = -std::numeric_limits<double>::infinity();
	double m_totalSpeed = 0;

	double m_sumX = 0;
	double m_sumY = 0;

	unsigned m_count = 0;
};

class CStats
{
public:
	void Update(double value)
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}
		m_accValue += value;

		++m_countAcc;
	}

	double GetMin() const
	{
		return m_minValue;
	}

	double GetMax() const
	{
		return m_maxValue;
	}

	double GetAverage() const
	{
		return m_accValue / m_countAcc;
	}

private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;

	unsigned m_countAcc = 0;
};