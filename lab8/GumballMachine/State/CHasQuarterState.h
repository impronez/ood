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
            m_gumballMachine.OutputInfo("You can't insert another quarter");
        }
        void EjectQuarter() override
        {
            m_gumballMachine.OutputInfo("Quarter returned");
            m_gumballMachine.SetNoQuarterState();
        }
        void TurnCrank() override
        {
            m_gumballMachine.OutputInfo("You turned...");
            m_gumballMachine.SetSoldState();
        }
        void Dispense() override
        {
            m_gumballMachine.OutputInfo("No gumball dispensed");
        }
        [[nodiscard]] std::string ToString() const override
        {
            return "waiting for turn of crank";
        }
    private:
        IGumballMachine & m_gumballMachine;
    };
}