#pragma once
#include <iostream>

#include "IState.h"
#include "../Machine/IGumballMachine.h"

namespace with_state
{
    class CSoldOutState final : public IState
    {
    public:
        explicit CSoldOutState(IGumballMachine & gumballMachine)
            :m_gumballMachine(gumballMachine)
        {}

        void InsertQuarter() override
        {
            std::cout << "You can't insert a quarter, the machine is sold out\n";
        }
        void EjectQuarter() override
        {
            std::cout << "You can't eject, you haven't inserted a quarter yet\n";
        }
        void TurnCrank() override
        {
            std::cout << "You turned but there's no gumballs\n";
        }
        void Dispense() override
        {
            std::cout << "No gumball dispensed\n";
        }
        [[nodiscard]] std::string ToString() const override
        {
            return "sold out";
        }
    private:
        IGumballMachine & m_gumballMachine;
    };
}