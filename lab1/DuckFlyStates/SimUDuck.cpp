#include "DecoyDuck.h"
#include "MallardDuck.h"
#include "ModelDuck.h"
#include "RedheadDuck.h"
#include "RubberDuck.h"
#include "DuckFunctions.h"
#include "FlyWithWings.h"
#include "DanceWaltz.h"
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
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(std::make_unique<FlyWithWings>());
	PlayWithDuck(modelDuck);
	PlayWithDuck(modelDuck);

	return EXIT_SUCCESS;
}