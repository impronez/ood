#pragma once
#include <iostream>

#include "IState.h"
#include "../Machine/IGumballMachine.h"

namespace with_state
{
    class CNoQuarterState final : public IState
    {
    public:
        explicit CNoQuarterState(IGumballMachine & gumballMachine)
            : m_gumballMachine(gumballMachine)
        {}

        void InsertGumballs(unsigned count) override
        {
            m_gumballMachine.AddGumballs(count);
        }

        void InsertQuarter() override
        {
            m_gumballMachine.AddQuarter();
            m_gumballMachine.SetHasQuarterState();
        }
        void EjectQuarter() override
        {
            m_gumballMachine.ReleaseAllQuarters();
        }
        void TurnCrank() override
        {
            m_gumballMachine.OutputInfo("You turned but there's no quarter");
        }
        void Dispense() override
        {
            m_gumballMachine.OutputInfo("You need to pay first");
        }
        [[nodiscard]] std::string ToString() const override
        {
            return "waiting for quarter";
        }
    private:
        IGumballMachine & m_gumballMachine;
    };
}