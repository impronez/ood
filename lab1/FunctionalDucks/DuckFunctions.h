#include "Duck.h"

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Sound();
	duck.Fly();
	duck.Dance();
	std::cout << std::endl;
}