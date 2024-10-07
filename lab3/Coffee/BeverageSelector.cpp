#pragma once

#include "BeverageSelector.h"
#include "Beverages.h"
#include "Condiments.h"
#include <map>
#include <functional>
#include <iostream>

using namespace std;

const int COFFEE_CHOICE = 1;
const int CAPPUCCINO_CHOICE = 2;
const int LATTE_CHOICE = 3;
const int TEA_CHOICE = 4;
const int MILKSHAKE_CHOICE = 5;

const int LEMON_CHOICE = 1;
const int CINNAMON_CHOICE = 2;
const int ICE_CUBES_CHOICE = 3;
const int CHOCOLATE_CRUMBS_CHOICE = 4;
const int COCONUT_FLAKES_CHOICE = 5;
const int SYRUP_CHOICE = 6;
const int CHOCOLATE_SLICES_CHOICE = 7;
const int CREAM_CHOICE = 8;
const int LIQUOR_CHOICE = 9;

const map<int, string> BEVERAGES =
{
	{ COFFEE_CHOICE, "Coffee" },
	{ CAPPUCCINO_CHOICE, "Cappuccino" },
	{ LATTE_CHOICE, "Latte" },
	{ TEA_CHOICE, "Tea" },
	{ MILKSHAKE_CHOICE, "Milkshake" }
};

const map<int, string> CONDIMENTS =
{
	{ LEMON_CHOICE, "Lemon" },
	{ CINNAMON_CHOICE, "Cinnamon" },
	{ ICE_CUBES_CHOICE, "Ice Cubes" },
	{ CHOCOLATE_CRUMBS_CHOICE, "Chocolate Crumbs" },
	{ COCONUT_FLAKES_CHOICE, "Coconut Flakes" },
	{ SYRUP_CHOICE, "Syrup" },
	{ CHOCOLATE_SLICES_CHOICE, "Chocolate Slices" },
	{ CREAM_CHOICE, "Cream" },
	{ LIQUOR_CHOICE, "Liquor" }
};

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона:
	Condiment - класс добавки, конструктор которого в качестве первого аргумента
				принимает IBeveragePtr&& оборачиваемого напитка
	Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto&& b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
		};
}

template <typename Component, typename Decorator>
auto operator << (Component&& component, const Decorator& decorate)
{
	return decorate(forward<Component>(component));
}

bool MakeCoffee(unique_ptr<IBeverage>& beverage)
{
	beverage = make_unique<CCoffee>();
	return true;
}

bool MakeCappuccino(unique_ptr<IBeverage>& beverage)
{
	cout << "Choose Cappuccino portion (1 - Standard, 2 - Double): ";

	int cappuccinoChoice;
	cin >> cappuccinoChoice;

	if (cappuccinoChoice < 1 || cappuccinoChoice > 2)
	{
		cout << "Invalid cappuccino portion!\n";
		return false;
	}

	beverage = make_unique<CCappuccino>(cappuccinoChoice != 1);
	return true;
}

bool MakeLatte(unique_ptr<IBeverage>& beverage)
{
	cout << "Choose Latte portion (1 - Standard, 2 - Double): ";

	int latteChoice;
	cin >> latteChoice;

	if (latteChoice < 1 || latteChoice > 2)
	{
		cout << "Invalid Latte portion choice";
		return false;
	}

	beverage = make_unique<CLatte>(latteChoice != 1);
	return true;
}

bool MakeTea(unique_ptr<IBeverage>& beverage)
{
	cout << "Choose tea type (1 - Black, 2 - Green, 3 - Herbal, 4 - Oolong): ";

	int teaChoice;
	cin >> teaChoice;

	if (teaChoice > 4 || teaChoice < 1)
	{
		cout << "Invalid choice, go away from my cafe!";
		return false;
	}

	beverage = make_unique<CTea>(static_cast<TeaType>(teaChoice - 1));
	return true;
}

bool MakeMilkshake(unique_ptr<IBeverage>& beverage)
{
	cout << "Choose milkshake size (1 - Small, 2 - Medium, 3 - Large): ";

	int sizeChoice;
	cin >> sizeChoice;

	if (sizeChoice > 3 || sizeChoice < 1)
	{
		cout << "Invalid choice, go away from my cafe!";
		return false;
	}

	beverage = make_unique<CMilkshake>(static_cast<MilkshakeSize>(sizeChoice - 1));
	return true;
}

bool MakeBeverageFromChoice(unique_ptr<IBeverage>& beverage, int choice)
{
	switch (choice)
	{
	case COFFEE_CHOICE: return MakeCoffee(beverage);
	case CAPPUCCINO_CHOICE: return MakeCappuccino(beverage);
	case LATTE_CHOICE: return MakeLatte(beverage);
	case TEA_CHOICE: return MakeTea(beverage);
	case MILKSHAKE_CHOICE: return MakeMilkshake(beverage);
	default:
		cout << "Invalid choice, go away from my cafe!" << endl;
		return false;
	}
}

bool MakeLemon(unique_ptr<IBeverage>& beverage)
{
	beverage = std::move(beverage) << MakeCondiment<CLemon>(2);
	return true;
}

bool MakeCinnamon(unique_ptr<IBeverage>& beverage)
{
	beverage = std::move(beverage) << MakeCondiment<CCinnamon>();
	return true;
}

bool MakeIceCubes(unique_ptr<IBeverage>& beverage)
{
	cout << "Choose Ice Cubes Type (1 - Water, 2 - Dry): ";

	int cubeChoice;
	cin >> cubeChoice;

	if (cubeChoice > 2 || cubeChoice < 1)
	{
		cout << "Invalid choice, try again)";
		return false;
	}
	beverage = std::move(beverage) << MakeCondiment<CIceCubes>
		(2, cubeChoice == 1 ? IceCubeType::Water : IceCubeType::Dry);
	return true;
}

bool MakeChocolateCrumbs(unique_ptr<IBeverage>& beverage)
{
	beverage = std::move(beverage) << MakeCondiment<CChocolateCrumbs>(5);
	return true;
}

bool MakeCoconutFlakes(unique_ptr<IBeverage>& beverage)
{
	beverage = std::move(beverage) << MakeCondiment<CCoconutFlakes>(5);
	return true;
}

bool MakeSyrup(unique_ptr<IBeverage>& beverage)
{
	cout << "Choose Syrup Type (1 - Maple, 2 - Chocolate): ";
	int syrupChoice;

	cin >> syrupChoice;
	if (syrupChoice > 2 || syrupChoice < 1)
	{
		cout << "Invalid Syrup Type choice";
		return false;
	}

	beverage = std::move(beverage) << MakeCondiment<CSyrup>
		(syrupChoice == 1 ? SyrupType::Maple : SyrupType::Chocolate);
	return true;
}

bool MakeCream(unique_ptr<IBeverage>& beverage)
{
	beverage = std::move(beverage) << MakeCondiment<CCream>();
	return true;
}

bool MakeChocolateSlices(unique_ptr<IBeverage>& beverage)
{
	cout << "Choose count slices (max 5): ";
	int slices;

	cin >> slices;
	try
	{
		beverage = std::move(beverage) << MakeCondiment<CChocolate>(slices);
	}
	catch (const std::invalid_argument& e)
	{
		cout << e.what() << std::endl;
		return false;
	}

	return true;
}

bool MakeLiquor(unique_ptr<IBeverage>& beverage)
{
	cout << "Choose Liquor Type (1 - Chocolate, 2 - Nutty): ";
	int liquorChoice;

	cin >> liquorChoice;
	if (liquorChoice > 2 or liquorChoice < 1)
	{
		cout << "Invalid choice Liquor Type";
		return false;
	}

	beverage = std::move(beverage) << MakeCondiment<CLiquor>
		(liquorChoice == 1 ? LiquorType::Chocolate : LiquorType::Nutty);
	return true;
}

bool MakeCondimentFromChoice(unique_ptr<IBeverage>& beverage, int choice)
{
	switch (choice)
	{
	case LEMON_CHOICE: return MakeLemon(beverage);
	case CINNAMON_CHOICE: return MakeCinnamon(beverage);
	case ICE_CUBES_CHOICE: return MakeIceCubes(beverage);
	case CHOCOLATE_CRUMBS_CHOICE: return MakeChocolateCrumbs(beverage);
	case COCONUT_FLAKES_CHOICE: return MakeCoconutFlakes(beverage);
	case SYRUP_CHOICE: return MakeSyrup(beverage);
	case CREAM_CHOICE: return MakeCream(beverage);
	case CHOCOLATE_SLICES_CHOICE: return MakeChocolateSlices(beverage);
	case LIQUOR_CHOICE: return MakeLiquor(beverage);
	default:
		cout << "Break" << endl;
		cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
		return false;
	}
}

void DialogWithUser()
{
	unique_ptr<IBeverage> beverage;

	cout << "Choose a beverage:\n";
	for (auto i : BEVERAGES)
	{
		cout << i.first << " - " << i.second << endl;
	}

	int beverageChoice;
	cin >> beverageChoice;

	if (MakeBeverageFromChoice(beverage, beverageChoice))
	{
		while (true)
		{
			cout << "Choose your condiment:\n";
			for (auto i : CONDIMENTS)
			{
				cout << i.first << " - " << i.second << endl;
			}
			cout << "Another number - Break\n";

			int condimentChoice;
			cin >> condimentChoice;

			if (!MakeCondimentFromChoice(beverage, condimentChoice))
			{
				break;
			}
		}
	}
}