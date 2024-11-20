#include <gtest/gtest.h>

#include "../Machine/CGumballMachine.h"

namespace
{
    std::string GetMachineState(unsigned count, const std::string& state)
    {
        return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
)",
            count,
            (count != 1 ? "s" : ""),
            state
        );
    }
}

TEST(CGumballMachine, InitializeTestWithoutGum)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithoutGumb(0, out);
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
}

TEST(CGumballMachine, InitializeTestWithGum)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithGumb(1, out);
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for quarter"));
}

TEST(CGumballMachine, EjectQuarterCommandInSoldOutState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithoutGumb(0, out);
    machineWithoutGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "You can't eject, you haven't inserted a quarter yet\n");
}

TEST(CGumballMachine, EjectQuarterCommandInNoQuarterState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithGumb(1, out);
    machineWithGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "You haven't inserted a quarter\n");
}

TEST(CGumballMachine, EjectQuarterCommandInHasQuarterState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithGumb(1, out);

    machineWithGumb.InsertQuarter();
    out.str("");
    machineWithGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "Quarter returned\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for quarter"));
}

TEST(CGumballMachine, InsertQuarterCommandInSoldOutState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithoutGumb(0, out);

    machineWithoutGumb.InsertQuarter();
    EXPECT_EQ(out.str(), "You can't insert a quarter, the machine is sold out\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
}

TEST(CGumballMachine, InsertQuarterCommandInNoQuarterState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithGumb(1, out);
    machineWithGumb.InsertQuarter();

    EXPECT_EQ(out.str(), "You inserted a quarter\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for turn of crank"));
}

TEST(CGumballMachine, InsertQuarterCommandInHasQuarterState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithGumb(1, out);
    machineWithGumb.InsertQuarter();

    out.str("");
    machineWithGumb.InsertQuarter();

    EXPECT_EQ(out.str(), "You can't insert another quarter\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for turn of crank"));
}

TEST(CGumballMachine, TurnCrankCommandInNoQuarterState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithGumb(1, out);
    machineWithGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned but there's no quarter\nYou need to pay first\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for quarter"));
}

TEST(CGumballMachine, TurnCrankCommandInSoldOutState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithoutGumb(0, out);
    machineWithoutGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned but there's no gumballs\nNo gumball dispensed\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
}

TEST(CGumballMachine, TurnCrankCommandInHasQuarterState)
{
    std::ostringstream out;

    const with_state::CGumballMachine machineWithoutGumb(2, out);

    machineWithoutGumb.InsertQuarter();
    out.str("");
    machineWithoutGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned...\nA gumball comes rolling out the slot...\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(1, "waiting for quarter"));

    machineWithoutGumb.InsertQuarter();
    out.str("");
    machineWithoutGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
}