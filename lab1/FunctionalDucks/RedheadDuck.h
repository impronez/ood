#include "Duck.h"
#include "DanceBehavior.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings,
			Quack,
			DanceMinuet)
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};
