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
            std::cout << "You inserted a quarter\n";
            m_gumballMachine.SetHasQuarterState();
        }
        void EjectQuarter() override
        {
            std::cout << "You haven't inserted a quarter\n";
        }
        void TurnCrank() override
        {
            std::cout << "You turned but there's no quarter\n";
        }
        void Dispense() override
        {
            std::cout << "You need to pay first\n";
        }
        [[nodiscard]] std::string ToString() const override
        {
            return "waiting for quarter";
        }
    private:
        IGumballMachine & m_gumballMachine;
    };
}