#include <gtest/gtest.h>

#include "../Machine/CGumballMachine.h"

class TestMachine final : public with_state::IGumballMachine
{
public:
    explicit TestMachine(unsigned ballCount, std::ostream& out)
        : m_out(out),
        m_soldState(*this),
        m_hasQuarterState(*this),
        m_noQuarterState(*this),
        m_soldOutState(*this),
        m_state(&m_soldState),
        m_ballCount(ballCount)
    {}

    void InsertQuarter() const
    {
        m_state->InsertQuarter();
    }

    void EjectQuarter() const
    {
        m_state->EjectQuarter();
    }

    void TurnCrank() const
    {
        m_state->TurnCrank();
    }

    void Dispense() const
    {
        m_state->Dispense();
    }

    void SetBallsCount(unsigned count)
    {
        m_ballCount = count;
    }

    void ReleaseBall() override
    {
        if (m_ballCount != 0)
        {
            --m_ballCount;
        }
    }

    [[nodiscard]] std::string GetStateString() const
    {
        return m_state->ToString();
    }

    [[nodiscard]] unsigned GetBallCount() const override
    {
        return m_ballCount;
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

    with_state::CHasQuarterState m_hasQuarterState;
    with_state::CNoQuarterState m_noQuarterState;
    with_state::CSoldOutState m_soldOutState;
    with_state::CSoldState m_soldState;

    unsigned m_ballCount = 0;

    with_state::IState* m_state;

    std::ostream& m_out;
};

TEST(CHasQuarterState, InsertQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetHasQuarterState();

    machine.InsertQuarter();

    EXPECT_EQ(out.str(), "You can't insert another quarter\n");
}

TEST(CHasQuarterState, EjectQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetHasQuarterState();

    machine.EjectQuarter();
    EXPECT_EQ(out.str(), "Quarter returned\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");
}

TEST(CHasQuarterState, TurnCrankCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetHasQuarterState();

    machine.TurnCrank();
    EXPECT_EQ(out.str(), "You turned...\n");
    EXPECT_EQ(machine.GetStateString(), "delivering a gumball");
}

TEST(CHasQuarterState, DispenseCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetHasQuarterState();

    machine.Dispense();
    EXPECT_EQ(out.str(), "No gumball dispensed\n");
}

TEST(CHasQuarterState, ToStringCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetHasQuarterState();

    EXPECT_EQ(machine.GetStateString(), "waiting for turn of crank");
}

TEST(CNoQuarterState, InsertQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetNoQuarterState();

    machine.InsertQuarter();
    EXPECT_EQ(out.str(), "You inserted a quarter\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for turn of crank");
}

TEST(CNoQuarterState, EjectQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetNoQuarterState();

    machine.EjectQuarter();
    EXPECT_EQ(out.str(), "You haven't inserted a quarter\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");
}

TEST(CNoQuarterState, TurnCrankCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetNoQuarterState();

    machine.TurnCrank();
    EXPECT_EQ(out.str(), "You turned but there's no quarter\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");
}

TEST(CNoQuarterState, DispenseCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetNoQuarterState();

    machine.Dispense();
    EXPECT_EQ(out.str(), "You need to pay first\n");
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");
}

TEST(CNoQuarterState, ToStringCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetNoQuarterState();

    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");
}

TEST(CSoldOutState, InsertQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldOutState();

    machine.InsertQuarter();
    EXPECT_EQ(out.str(), "You can't insert a quarter, the machine is sold out\n");
}

TEST(CSoldOutState, EjectQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldOutState();

    machine.EjectQuarter();
    EXPECT_EQ(out.str(), "You can't eject, you haven't inserted a quarter yet\n");
}

TEST(CSoldOutState, TurnCrankCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldOutState();

    machine.TurnCrank();
    EXPECT_EQ(out.str(), "You turned but there's no gumballs\n");
}

TEST(CSoldOutState, DispenseCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldOutState();

    machine.Dispense();
    EXPECT_EQ(out.str(), "No gumball dispensed\n");
}

TEST(CSoldOutState, ToStringCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldOutState();

    EXPECT_EQ(machine.GetStateString(), "sold out");
}

TEST(CSoldState, InsertQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldState();

    machine.InsertQuarter();
    EXPECT_EQ(out.str(), "Please wait, we're already giving you a gumball\n");
}

TEST(CSoldState, EjectQuarterCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldState();

    machine.EjectQuarter();
    EXPECT_EQ(out.str(), "Sorry you already turned the crank\n");
}

TEST(CSoldState, TurnCrankCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldState();

    machine.TurnCrank();
    EXPECT_EQ(out.str(), "Turning twice doesn't get you another gumball\n");
}

TEST(CSoldState, DispenseCommand)
{
    std::ostringstream out;

    TestMachine machine(2, out);
    machine.SetSoldState();

    machine.Dispense();
    EXPECT_EQ(machine.GetBallCount(), 1);
    EXPECT_EQ(machine.GetStateString(), "waiting for quarter");

    machine.SetSoldState();

    machine.Dispense();
    EXPECT_EQ(machine.GetBallCount(), 0);
    EXPECT_EQ(machine.GetStateString(), "sold out");
    EXPECT_EQ(out.str(), "Oops, out of gumballs\n");
}

TEST(CSoldState, ToStringCommand)
{
    std::ostringstream out;

    TestMachine machine(5, out);
    machine.SetSoldState();

    EXPECT_EQ(machine.GetStateString(), "delivering a gumball");
}