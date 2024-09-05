#ifndef DANCEWALTZ_H
#define DANCEWALTZ_H

#include "IDanceBehavior.h"
#include <iostream>

class DanceWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dance a waltz!!" << std::endl;
	}
};

#endif