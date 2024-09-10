#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"
#include "../DecoyDuck.h"
#include "../MallardDuck.h"
#include "../ModelDuck.h"
#include "../RedheadDuck.h"
#include "../RubberDuck.h"
#include "../DanceWaltz.h"
#include <iostream>
#include <sstream>
#include <string>

const std::string DANCE_MINUET = "I'm dance a minuet!!\n";
const std::string DANCE_WALTZ = "I'm dance a waltz!!\n";

TEST_CASE("Test dance method of decoy duck")
{
	DecoyDuck decoyDuck;
	std::ostringstream output;

	std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

	decoyDuck.Dance();

	std::cout.rdbuf(originalCoutBuffer);

	REQUIRE(output.str().empty());
}

TEST_CASE("Test dance method of mallard duck")
{
	MallardDuck mallardDuck;
	std::ostringstream output;

	std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

	mallardDuck.Dance();

	std::cout.rdbuf(originalCoutBuffer);

	REQUIRE(output.str() == DANCE_WALTZ);
}

TEST_CASE("Test dance method of model duck")
{
	ModelDuck modelDuck;
	std::ostringstream output;

	std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

	modelDuck.Dance();

	std::cout.rdbuf(originalCoutBuffer);

	REQUIRE(output.str().empty());
}

TEST_CASE("Test dance method of redhead duck")
{
	RedheadDuck redheadDuck;
	std::ostringstream output;

	std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

	redheadDuck.Dance();

	std::cout.rdbuf(originalCoutBuffer);

	REQUIRE(output.str() == DANCE_MINUET);
}

TEST_CASE("Test dance method of rubber duck")
{
	RubberDuck rubberDuck;
	std::ostringstream output;

	std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

	rubberDuck.Dance();

	std::cout.rdbuf(originalCoutBuffer);

	REQUIRE(output.str().empty());
}

TEST_CASE("Test dance method of model duck with setting dance")
{
	ModelDuck modelDuck;
	std::ostringstream output;

	WHEN("Model duck is not dance")
	{
		std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

		modelDuck.Dance();

		std::cout.rdbuf(originalCoutBuffer);

		REQUIRE(output.str().empty());

		modelDuck.SetDanceBehavior(std::make_unique<DanceWaltz>());
		THEN("Model duck is dance waltz")
		{
			std::streambuf* originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

			modelDuck.Dance();

			std::cout.rdbuf(originalCoutBuffer);

			REQUIRE(output.str() == DANCE_WALTZ);
		}
	}

}