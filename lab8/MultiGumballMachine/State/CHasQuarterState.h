#pragma once
#include <iostream>

#include "IState.h"
#include "../Machine/IGumballMachine.h"

namespace with_state
{
    class CHasQuarterState final : public IState
    {
    public:
        explicit CHasQuarterState(IGumballMachine & gumballMachine)
            :m_gumballMachine(gumballMachine)
        {}

        void InsertQuarter() override
        {
            std::cout << "You can't insert another quarter\n";
        }
        void EjectQuarter() override
        {
            std::cout << "Quarter returned\n";
            m_gumballMachine.SetNoQuarterState();
        }
        void TurnCrank() override
        {
            std::cout << "You turned...\n";
            m_gumballMachine.SetSoldState();
        }
        void Dispense() override
        {
            std::cout << "No gumball dispensed\n";
        }
        [[nodiscard]] std::string ToString() const override
        {
            return "waiting for turn of crank";
        }
    private:
        IGumballMachine & m_gumballMachine;
    };
}