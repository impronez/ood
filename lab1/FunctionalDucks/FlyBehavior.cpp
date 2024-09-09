#include "FlyBehavior.h"
#include <iostream>

FlyBehavior FlyWithWings()
{
	return [flightNumber = 0]() mutable -> void
		{
			++flightNumber;
			std::cout << "I'm flying with wings!! Flight number: "
				<< flightNumber << std::endl;
		};
}

void FlyNoWay() {}