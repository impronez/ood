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
            m_gumballMachine.OutputInfo("You can't insert a quarter, the machine is sold out");
        }
        void EjectQuarter() override
        {
            m_gumballMachine.OutputInfo("You can't eject, you haven't inserted a quarter yet");
        }
        void TurnCrank() override
        {
            m_gumballMachine.OutputInfo("You turned but there's no gumballs");
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