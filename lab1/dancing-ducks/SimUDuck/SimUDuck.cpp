#include "DecoyDuck.h"
#include "MallardDuck.h"
#include "ModelDuck.h"
#include "RedheadDuck.h"
#include "RubberDuck.h"
#include "DuckFunctions.h"
#include <cstdlib>

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);

	modelDuck.SetFlyBehavior(std::make_unique<FlyWithWings>());
	modelDuck.SetDanceBehavior(std::make_unique<DanceWaltz>());
	PlayWithDuck(modelDuck);

	return EXIT_SUCCESS;
}