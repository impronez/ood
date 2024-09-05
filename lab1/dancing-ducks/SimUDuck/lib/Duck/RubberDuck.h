#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Duck.h"
#include "FlyNoWay.h"
#include "SqueakBehavior.h"
#include "NotDance.h"
#include <iostream>

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(std::make_unique<FlyNoWay>(),
			std::make_unique<SqueakBehavior>(),
			std::make_unique<NotDance>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};

#endif
