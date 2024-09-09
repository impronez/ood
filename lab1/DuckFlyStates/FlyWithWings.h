#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		++m_flightNumber;
		std::cout << "I'm flying with wings!! Flight number: "
			<< m_flightNumber << std::endl;
	}
private:
	int m_flightNumber = 0;
};

#endif