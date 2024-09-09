#include "Duck.h"
#include "DanceBehavior.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay,
			Squeak,
			NotDance)
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};