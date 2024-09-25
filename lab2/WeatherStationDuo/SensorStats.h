#pragma once
#include <climits>

class SensorStats
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

	double GetMin()
	{
		return m_minValue;
	}

	double GetMax()
	{
		return m_maxValue;
	}

	double GetAverage()
	{
		return m_accValue / m_countAcc;
	}

private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;

	unsigned m_countAcc = 0;
};