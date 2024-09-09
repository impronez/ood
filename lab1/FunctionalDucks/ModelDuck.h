#include "Duck.h"
#include "DanceBehavior.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay,
			Quack,
			NotDance)
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};