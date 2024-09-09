#include "Duck.h"
#include "DanceBehavior.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"


class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(),
			Quack,
			DanceWaltz)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};
