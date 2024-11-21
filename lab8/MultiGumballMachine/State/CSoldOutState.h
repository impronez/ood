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

        void InsertGumballs(unsigned count) override
        {
            if (count == 0)
            {
                return;
            }

            m_gumballMachine.AddGumballs(count);

            if (m_gumballMachine.GetQuarterCount() == 0)
            {
                m_gumballMachine.SetNoQuarterState();
            }
            else
            {
               m_gumballMachine.SetHasQuarterState();
            }
        }

        void InsertQuarter() override
        {
            m_gumballMachine.AddQuarter();
        }
        void EjectQuarter() override
        {
            m_gumballMachine.ReleaseAllQuarters();
        }
        void TurnCrank() override
        {
            m_gumballMachine.OutputInfo("You turned, but there's no gumballs");
        }
        void Dispense() override
        {
            m_gumballMachine.OutputInfo("No gumball dispensed");
        }
        [[nodiscard]] std::string ToString() const override
        {
            return "sold out";
        }
    private:
        IGumballMachine & m_gumballMachine;
    };
}