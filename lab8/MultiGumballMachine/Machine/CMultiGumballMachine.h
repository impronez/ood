#pragma once

#include <format>

#include "IGumballMachine.h"
#include "../State/CSoldState.h"
#include "../State/CSoldOutState.h"
#include "../State/CHasQuarterState.h"
#include "../State/CNoQuarterState.h"

namespace with_state
{
    class CMultiGumballMachine final : private IGumballMachine
    {
    public:
        explicit CMultiGumballMachine(unsigned numBalls)
            : m_soldState(*this)
            , m_soldOutState(*this)
            , m_noQuarterState(*this)
            , m_hasQuarterState(*this)
            , m_state(&m_soldOutState)
            , m_quarterCount(numBalls)
        {
            if (m_quarterCount > 0)
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
                m_quarterCount,
                (m_quarterCount != 1 ? "s" : ""),
                m_state->ToString()
            );
        }

        [[nodiscard]] unsigned GetQuarterCount() const override
        {
            return m_quarterCount;
        }

    private:
        [[nodiscard]] unsigned GetBallCount() const override
        {
            return m_gumballCount;
        }

        void Dispense() override
        {
            m_state->Dispense();
        }

        void ReleaseBall() override
        {
            if (m_quarterCount != 0)
            {
                std::cout << "A gumball comes rolling out the slot...\n";
                --m_quarterCount;
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

        void AddQuarter() override
        {
            if (m_quarterCount < MAX_QUARTER_COUNT)
            {
                ++m_quarterCount;
            }
            else
            {
                std::cout << "Quarter count is max (" << MAX_QUARTER_COUNT << ")\n";
            }
        }

        void ReleaseAllQuarters() override
        {
            m_quarterCount = 0;
        }

        void TakeQuarter() override
        {
            if (m_quarterCount > 0)
            {
                std::cout << "A quarter was taked from machine\n";
                --m_quarterCount;
            }
            else
            {
                std::cout << "Count quarter is 0\n";
            }
        }

        static constexpr unsigned MAX_QUARTER_COUNT = 5;

        unsigned m_quarterCount = 0;
        unsigned m_gumballCount = 0;

        CSoldState m_soldState;
        CSoldOutState m_soldOutState;
        CNoQuarterState m_noQuarterState;
        CHasQuarterState m_hasQuarterState;

        IState* m_state;
    };
}