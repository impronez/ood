#ifndef DECOYDUCK_H
#define DECOYDUCK_H

#include "Duck.h"
#include "FlyNoWay.h"
#include "MuteQuackBehavior.h"
#include "NotDance.h"
#include <iostream>
#include <memory>

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(std::make_unique<FlyNoWay>(),
			std::make_unique<MuteQuackBehavior>(),
			std::make_unique<NotDance>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};

#endif