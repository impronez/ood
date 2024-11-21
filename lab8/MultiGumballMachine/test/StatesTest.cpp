#include <gtest/gtest.h>

#include "../Machine/IGumballMachine.h"
#include "../State/CHasQuarterState.h"
#include "../State/CNoQuarterState.h"
#include "../State/CSoldOutState.h"
#include "../State/CSoldState.h"

class TestMachine final : public with_state::IGumballMachine
{
public:
    TestMachine(unsigned ballCount, std::ostream& out)
        : m_gumballCount(ballCount),
        m_hasQuarterState(*this),
        m_noQuarterState(*this),
        m_soldOutState(*this),
        m_soldState(*this),
        m_state(&m_soldOutState),
        m_out(out)
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

    [[nodiscard]] unsigned GetQuarterCount() const override
    {
        return m_quarterCount;
    }

    void AddQuarter() override
    {
        if (m_quarterCount < 5)
        {
            ++m_quarterCount;
        }
        else
        {
            m_out << "Quarter don't added. Quarter count is max (" << 5 << ")\n";
        }
    }

    void AddGumballs(unsigned count) override
    {
        m_gumballCount += count;
    }

    void ReleaseAllQuarters() override
    {
        if (m_quarterCount > 0)
        {
            m_quarterCount = 0;
        }
    }

    void TakeQuarter() override
    {
        --m_quarterCount;
    }

    void Dispense() override
    {
        m_state->Dispense();
    }

    void SetBallsCount(unsigned count)
    {
        m_gumballCount = count;
    }

    void ReleaseBall() override
    {
        if (m_gumballCount != 0)
        {
            --m_gumballCount;
        }
    }

    [[nodiscard]] std::string GetStateString() const
    {
        return m_state->ToString();
    }

    [[nodiscard]] unsigned GetBallCount() const override
    {
        return m_gumballCount;
    }

    void OutputInfo(const std::string &info) override
    {
        m_out << info << std::endl;
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

    unsigned m_quarterCount = 0;
    unsigned m_gumballCount = 0;

    with_state::CHasQuarterState m_hasQuarterState;
    with_state::CNoQuarterState m_noQuarterState;
    with_state::CSoldOutState m_soldOutState;
    with_state::CSoldState m_soldState;

    with_state::IState* m_state;

    std::ostream& m_out;
};

TEST(CHasQuarterState, InsertGumballsCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.InsertQuarter();

    machine.InsertGumballs(4);

    EXPECT_EQ(machine.GetBallCount(), 5);
}

TEST(CHasQuarterState, InsertQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.InsertQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 1);

    machine.InsertQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 2);
}

TEST(CHasQuarterState, EjectQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.InsertQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 1);

    out.str("");

    machine.EjectQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 0);
}

TEST(CHasQuarterState, TurnCrankCommand)
{
    std::ostringstream out;

    TestMachine machine(2, out);

    machine.InsertQuarter();

    machine.TurnCrank();

    EXPECT_EQ(out.str(), "You turned...\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");
}

TEST(CHasQuarterState, DispenseCommand)
{
    std::ostringstream out;

    TestMachine machine(2, out);

    machine.InsertQuarter();
    machine.Dispense();

    EXPECT_EQ(out.str(), "No gumball dispensed\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for turn of crank");
}

TEST(CNoQuarterState, InsertGumballsCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.InsertGumballs(4);

    EXPECT_EQ(machine.GetBallCount(), 5);
}

TEST(CNoQuarterState, InsertQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.InsertQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 1);
    EXPECT_EQ(machine.GetStateString(), "waiting for turn of crank");
}

TEST(CNoQuarterState, EjectQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.EjectQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 0);
}

TEST(CNoQuarterState, TurnCrankCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.TurnCrank();

    EXPECT_EQ(out.str(), "You turned but there's no quarter\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");
}

TEST(CNoQuarterState, DispenseCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.Dispense();

    EXPECT_EQ(out.str(), "You need to pay first\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");
}

TEST(CSoldOutState, InsertGumballsCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.SetSoldOutState();
    machine.InsertGumballs(0);
    EXPECT_EQ(machine.GetBallCount(), 0);
    EXPECT_EQ(machine.GetStateString(), "sold out");

    machine.SetSoldOutState();

    machine.InsertGumballs(3);
    EXPECT_EQ(machine.GetBallCount(), 3);
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");

    machine.m_gumballCount = 0;
    machine.SetNoQuarterState();
    machine.InsertQuarter();

    machine.SetSoldOutState();
    machine.InsertGumballs(1);
    EXPECT_EQ(machine.GetBallCount(), 1);
    EXPECT_EQ(machine.GetStateString(), "waiting for turn of crank");
}

TEST(CSoldOutState, InsertQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.InsertQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 1);
}

TEST(CSoldOutState, EjectQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.EjectQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 0);

    machine.InsertQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 1);

    machine.EjectQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 0);
}

TEST(CSoldOutState, TurnCrankCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.TurnCrank();

    EXPECT_EQ(out.str(), "You turned, but there's no gumballs\n");
}

TEST(CSoldOutState, DispenseCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.Dispense();

    EXPECT_EQ(out.str(), "No gumball dispensed\n");
    EXPECT_EQ(machine.GetStateString(), "sold out");
}

TEST(CSoldState, InsertGumballsCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.SetSoldState();

    machine.InsertGumballs(0);
    EXPECT_EQ(out.str(), "");

    machine.InsertGumballs(1);
    EXPECT_EQ(out.str(), "You can't insert a gumballs in sold state\n");
}

TEST(CSoldState, InsertQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.SetSoldState();

    machine.InsertQuarter();
    EXPECT_EQ(out.str(), "Please wait, we're already giving you a gumball\n");
}

TEST(CSoldState, EjectQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.SetSoldState();

    machine.EjectQuarter();
    EXPECT_EQ(out.str(), "Sorry you already turned the crank\n");
}

TEST(CSoldState, TurnCrankCommand)
{
    std::ostringstream out;

    TestMachine machine(0, out);
    machine.SetSoldState();

    machine.TurnCrank();
    EXPECT_EQ(out.str(), "Turning twice doesn't get you another gumball\n");
}

TEST(CSoldState, DispenseCommand)
{
    std::ostringstream out;

    TestMachine machine(1, out);
    machine.InsertQuarter();
    machine.SetSoldState();

    machine.Dispense();

    EXPECT_EQ(machine.GetQuarterCount(), 0);
    EXPECT_EQ(machine.GetBallCount(), 0);
    EXPECT_EQ(machine.GetStateString(), "sold out");

    machine.InsertGumballs(3);
    machine.InsertQuarter();

    machine.SetSoldState();
    machine.Dispense();

    EXPECT_EQ(machine.GetQuarterCount(), 0);
    EXPECT_EQ(machine.GetBallCount(), 2);
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");

    machine.InsertQuarter();
    machine.InsertQuarter();
    machine.SetSoldState();
    machine.Dispense();

    EXPECT_EQ(machine.GetStateString(), "waiting for turn of crank");
}

TEST(CSoldState, ToStringCommand)
{
    std::ostringstream out;
    TestMachine machine(0, out);
    machine.SetSoldState();

    EXPECT_EQ(machine.GetStateString(), "delivering a gumball");
}