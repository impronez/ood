#pragma once
#include <iostream>

#include "IState.h"
#include "../Machine/IGumballMachine.h"

namespace with_state
{
    class CNoQuarterState final : public IState // монета не вставлена
    {
    public:
        explicit CNoQuarterState(IGumballMachine & gumballMachine)
            : m_gumballMachine(gumballMachine)
        {}

        void InsertQuarter() override
        {
            m_gumballMachine.OutputInfo("You inserted a quarter");
            m_gumballMachine.SetHasQuarterState();
        }
        void EjectQuarter() override
        {
            m_gumballMachine.OutputInfo("You haven't inserted a quarter");
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