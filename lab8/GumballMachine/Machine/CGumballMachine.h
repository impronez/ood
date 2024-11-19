#pragma once

#include <format>

#include "IGumballMachine.h"
#include "../State/CSoldState.h"
#include "../State/CSoldOutState.h"
#include "../State/CHasQuarterState.h"
#include "../State/CNoQuarterState.h"

namespace with_state
{
    class CGumballMachine final : private IGumballMachine
    {
    public:
        explicit CGumballMachine(unsigned numBalls, std::ostream& out)
            : m_soldState(*this)
            , m_soldOutState(*this)
            , m_noQuarterState(*this)
            , m_hasQuarterState(*this)
            , m_state(&m_soldOutState)
            , m_count(numBalls)
            , m_out(out)
        {
            if (m_count > 0)
            {
                m_state = &m_noQuarterState;
            }
        }

        void EjectQuarter() const
        {
            m_state->EjectQuarter();
        }

        void InsertQuarter() const
        {
            m_state->InsertQuarter();
        }

        void TurnCrank() const
        {
            m_state->TurnCrank();
            m_state->Dispense();
        }

        [[nodiscard]] std::string ToString() const
        {
            return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
)",
                m_count,
                (m_count != 1 ? "s" : ""),
                m_state->ToString()
            );
        }

    private:

        [[nodiscard]] unsigned GetBallCount() const override
        {
            return m_count;
        }

        void ReleaseBall() override
        {
            if (m_count != 0)
            {
                m_out << "A gumball comes rolling out the slot...\n";
                --m_count;
            }
        }

        void SetSoldOutState() override
        {
            m_state = &m_soldOutState;
        }

        void SetNoQuarterState() override
        {
            m_state = &m_noQuarterState;
        }

        void SetSoldState() override
        {
            m_state = &m_soldState;
        }

        void SetHasQuarterState() override
        {
            m_state = &m_hasQuarterState;
        }

        void OutputInfo(const std::string &info) override
        {
            m_out << info << std::endl;
        }

        unsigned m_count = 0;

        CSoldState m_soldState;
        CSoldOutState m_soldOutState;
        CNoQuarterState m_noQuarterState;
        CHasQuarterState m_hasQuarterState;

        IState* m_state;

        std::ostream& m_out;
    };
}