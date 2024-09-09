#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Duck.h"
#include "FlyWithWings.h"
#include "QuackBehavior.h"
#include "DanceMinuet.h"

#include <memory>

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(std::make_unique<FlyWithWings>(),
			std::make_unique<QuackBehavior>(),
			std::make_unique<DanceMinuet>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};

#endif
