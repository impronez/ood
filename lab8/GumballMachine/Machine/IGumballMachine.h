#pragma once

namespace with_state
{
    struct IGumballMachine // контекст
    {
        virtual void ReleaseBall() = 0;
        [[nodiscard]] virtual unsigned GetBallCount() const = 0;

        virtual void SetSoldOutState() = 0;
        virtual void SetNoQuarterState() = 0;
        virtual void SetSoldState() = 0;
        virtual void SetHasQuarterState() = 0;

        virtual void OutputInfo(const std::string& info) = 0;

        virtual ~IGumballMachine() = default;
    };
}