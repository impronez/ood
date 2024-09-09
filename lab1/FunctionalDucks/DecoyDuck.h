#include "Duck.h"
#include "DanceBehavior.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay,
			MuteQuack,
			NotDance)
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};