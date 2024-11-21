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

        void InsertGumballs(unsigned count) override
        {
            m_gumballMachine.AddGumballs(count);
        }

        void InsertQuarter() override
        {
            m_gumballMachine.AddQuarter();
        }
        void EjectQuarter() override
        {
            m_gumballMachine.ReleaseAllQuarters();
            m_gumballMachine.SetNoQuarterState();
        }
        void TurnCrank() override
        {
            m_gumballMachine.OutputInfo("You turned...");
            m_gumballMachine.SetSoldState();
            m_gumballMachine.Dispense();
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