#include "MallardDuck.h"
#include "DecoyDuck.h"
#include "RedheadDuck.h"
#include "RubberDuck.h"
#include "ModelDuck.h"
#include "DuckFunctions.h"

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

	modelDuck.SetFlyBehavior(FlyWithWings());
	PlayWithDuck(modelDuck);
	PlayWithDuck(modelDuck);

	return EXIT_SUCCESS;
}