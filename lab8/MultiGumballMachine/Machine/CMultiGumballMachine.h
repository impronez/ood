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
        explicit CMultiGumballMachine(unsigned numBalls, std::ostream& out)
            : m_soldState(*this)
            , m_soldOutState(*this)
            , m_noQuarterState(*this)
            , m_hasQuarterState(*this)
            , m_state(&m_soldOutState)
            , m_gumballCount(numBalls)
            , m_out(out)
        {
            if (m_gumballCount > 0)
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

        void InsertGumballs(unsigned count) const
        {
            m_state->InsertGumballs(count);
        }

        void TurnCrank() const
        {
            m_state->TurnCrank();
        }

        [[nodiscard]] std::string ToString() const
        {
            return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
)",
                m_gumballCount,
                (m_gumballCount != 1 ? "s" : ""),
                m_state->ToString()
            );
        }

        [[nodiscard]] unsigned GetQuarterCount() const override
        {
            return m_quarterCount;
        }

        [[nodiscard]] unsigned GetBallCount() const override
        {
            return m_gumballCount;
        }

    private:

        void AddGumballs(unsigned count) override
        {
            if (count != 0)
            {
                m_gumballCount += count;
                m_out << "You inserted a gumballs" << std::endl;
            }
        }

        void Dispense() override
        {
            m_state->Dispense();
        }

        void ReleaseBall() override
        {
            if (m_gumballCount != 0)
            {
                m_out << "A gumball comes rolling out the slot...\n";
                --m_gumballCount;
            }
        }

        void ReleaseAllQuarters() override
        {
            if (m_quarterCount > 0)
            {
                m_out << "Quarters are ejected\n";
                m_quarterCount = 0;
            }
            else
            {
                m_out << "Quarters are not inserted\n";
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
                m_out << "You inserted a quarter. Count quarter is " << m_quarterCount << std::endl;
            }
            else
            {
                m_out << "Quarter don't added. Quarter count is max (" << MAX_QUARTER_COUNT << ")\n";
            }
        }

        void TakeQuarter() override
        {
            if (m_quarterCount > 0)
            {
                --m_quarterCount;
                m_out << "A quarter was taked in machine. Quarter count is " << m_quarterCount << std::endl;
            }
        }

        void OutputInfo(const std::string &info) override
        {
            m_out << info << std::endl;
        }

        static constexpr unsigned MAX_QUARTER_COUNT = 5;

        unsigned m_quarterCount = 0;
        unsigned m_gumballCount = 0;

        CSoldState m_soldState;
        CSoldOutState m_soldOutState;
        CNoQuarterState m_noQuarterState;
        CHasQuarterState m_hasQuarterState;

        IState* m_state;

        std::ostream& m_out;
    };
}