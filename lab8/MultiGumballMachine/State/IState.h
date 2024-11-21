#pragma once

namespace with_state
{
    struct IState
    {
        virtual void InsertGumballs(unsigned count) = 0;
        virtual void InsertQuarter() = 0;
        virtual void EjectQuarter() = 0;
        virtual void TurnCrank() = 0;
        virtual void Dispense() = 0;
        [[nodiscard]] virtual std::string ToString()const = 0;
        virtual ~IState() = default;
    };
}