#include <iostream>
#include <memory>

#include "CommandHandler.h"
#include "Machine/CMultiGumballMachine.h"

using namespace std;

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType & m)
{
    cout << m.ToString() << endl;

    m.InsertQuarter();
    m.TurnCrank();

    cout << m.ToString() << endl;

    m.InsertQuarter();
    m.EjectQuarter();
    m.TurnCrank();

    cout << m.ToString() << endl;

    m.InsertQuarter();
    m.TurnCrank();
    m.InsertQuarter();
    m.TurnCrank();
    m.EjectQuarter();

    cout << m.ToString() << endl;

    m.InsertQuarter();
    m.InsertQuarter();
    m.TurnCrank();
    m.InsertQuarter();
    m.TurnCrank();
    m.InsertQuarter();
    m.TurnCrank();

    cout << m.ToString() << endl;
}

int main()
{
    auto gumballMachine = std::make_unique<with_state::CMultiGumballMachine>(5, std::cout);

    CommandHandler handler((std::move(gumballMachine)));
    handler.Run();

    return 0;
}