#pragma once

#include "IBeverage.h"

bool MakeCoffee(std::unique_ptr<IBeverage>& beverage);

bool MakeCappuccino(std::unique_ptr<IBeverage>& beverage);

bool MakeLatte(std::unique_ptr<IBeverage>& beverage);

bool MakeTea(std::unique_ptr<IBeverage>& beverage);

bool MakeMilkshake(std::unique_ptr<IBeverage>& beverage);

bool MakeBeverageFromChoice(std::unique_ptr<IBeverage>& beverage, int choice);

bool MakeLemon(std::unique_ptr<IBeverage>& beverage);

bool MakeCinnamon(std::unique_ptr<IBeverage>& beverage);

bool MakeIceCubes(std::unique_ptr<IBeverage>& beverage);

bool MakeChocolateCrumbs(std::unique_ptr<IBeverage>& beverage);

bool MakeCoconutFlakes(std::unique_ptr<IBeverage>& beverage);

bool MakeSyrup(std::unique_ptr<IBeverage>& beverage);

bool MakeCream(std::unique_ptr<IBeverage>& beverage);

bool MakeChocolateSlices(std::unique_ptr<IBeverage>& beverage);

bool MakeLiquor(std::unique_ptr<IBeverage>& beverage);

bool MakeCondimentFromChoice(std::unique_ptr<IBeverage>& beverage, int choice);

void DialogWithUser();