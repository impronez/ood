#pragma once
#include <iostream>

#include "IState.h"
#include "../Machine/IGumballMachine.h"

namespace with_state
{
    class CSoldState final : public IState
    {
    public:
        explicit CSoldState(IGumballMachine & gumballMachine)
            : m_gumballMachine(gumballMachine)
        {}

        void InsertGumballs(unsigned count) override
        {
            if (count != 0)
            {
                m_gumballMachine.OutputInfo("You can't insert a gumballs in sold state");
            }
        }

        void InsertQuarter() override
        {
            m_gumballMachine.OutputInfo("Please wait, we're already giving you a gumball");
        }
        void EjectQuarter() override
        {
            m_gumballMachine.OutputInfo("Sorry you already turned the crank");
        }
        void TurnCrank() override
        {
            m_gumballMachine.OutputInfo("Turning twice doesn't get you another gumball");
        }
        void Dispense() override
        {
            m_gumballMachine.TakeQuarter();
            m_gumballMachine.ReleaseBall();

            if (m_gumballMachine.GetBallCount() == 0)
            {
                m_gumballMachine.OutputInfo("Oops, out of gumballs");
                m_gumballMachine.SetSoldOutState();
            }
            else
            {
                if (!m_gumballMachine.GetQuarterCount())
                {
                    m_gumballMachine.SetNoQuarterState();
                }
                else
                {
                    m_gumballMachine.SetHasQuarterState();
                }
            }
        }
        [[nodiscard]] std::string ToString() const override
        {
            return "delivering a gumball";
        }
    private:
        IGumballMachine & m_gumballMachine;
    };
}