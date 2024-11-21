#include <gtest/gtest.h>
#include <format>

#include "../Machine/CMultiGumballMachine.h"

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

TEST(CMultiGumballMachine, InitializeTestWithoutGum)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithoutGumb(0, out);
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
    EXPECT_EQ(machineWithoutGumb.GetBallCount(), 0);
}

TEST(CMultiGumballMachine, InitializeTestWithGum)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithGumb(1, out);
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for quarter"));
    EXPECT_EQ(machineWithGumb.GetBallCount(), 1);
}

TEST(CMultiGumballMachine, EjectQuarterCommandInSoldOutState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithoutGumb(0, out);
    machineWithoutGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "Quarters are not inserted\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
}

TEST(CMultiGumballMachine, EjectQuarterCommandInNoQuarterState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithGumb(1, out);
    machineWithGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "Quarters are not inserted\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for quarter"));
}

TEST(CMultiGumballMachine, EjectQuarterCommandInHasQuarterState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithGumb(1, out);

    machineWithGumb.InsertQuarter();
    out.str("");
    machineWithGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "Quarters are ejected\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for quarter"));
    EXPECT_EQ(machineWithGumb.GetQuarterCount(), 0);
}

TEST(CMultiGumballMachine, InsertQuarterCommandInSoldOutState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithoutGumb(0, out);

    machineWithoutGumb.InsertQuarter();
    EXPECT_EQ(out.str(), "You inserted a quarter. Count quarter is 1\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));

    machineWithoutGumb.InsertQuarter();
    machineWithoutGumb.InsertQuarter();
    machineWithoutGumb.InsertQuarter();
    machineWithoutGumb.InsertQuarter();

    out.str("");

    machineWithoutGumb.InsertQuarter();
    EXPECT_EQ(out.str(), "Quarter don't added. Quarter count is max (5)\n");
}

TEST(CMultiGumballMachine, InsertQuarterCommandInNoQuarterState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithGumb(1, out);
    machineWithGumb.InsertQuarter();

    EXPECT_EQ(out.str(), "You inserted a quarter. Count quarter is 1\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for turn of crank"));
}

TEST(CMultiGumballMachine, InsertQuarterCommandInHasQuarterState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithGumb(1, out);
    machineWithGumb.InsertQuarter();

    out.str("");
    machineWithGumb.InsertQuarter();

    EXPECT_EQ(out.str(), "You inserted a quarter. Count quarter is 2\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for turn of crank"));

    for (int i = 0; i < 4; i++)
    {
        machineWithGumb.InsertQuarter();
    }

    out.str("");

    machineWithGumb.InsertQuarter();
    EXPECT_EQ(out.str(), "Quarter don't added. Quarter count is max (5)\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(1, "waiting for turn of crank"));
}

TEST(CMultiGumballMachine, TurnCrankInSoldOutState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithoutGumb(0, out);

    machineWithoutGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned, but there's no gumballs\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
}

TEST(CMultiGumballMachine, TurnCrankInNoQuarterState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithoutGumb(1, out);

    machineWithoutGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned but there's no quarter\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(1, "waiting for quarter"));
}

TEST(CMultiGumballMachine, TurnCrankInHasQuarterState)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machineWithoutGumb(1, out);
    machineWithoutGumb.InsertQuarter();
    out.str("");

    machineWithoutGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned...\nA quarter was taked in machine. Quarter count is 0\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
}

TEST(CMultiGumballMachine, GetQuarterCountCommand)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machine(1, out);

    machine.InsertQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 1);

    machine.InsertQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 2);

    machine.InsertQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 3);

    machine.InsertQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 4);

    machine.InsertQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 5);

    machine.InsertQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 5);
}

TEST(CMultiGumballMachine, GetBallCountCommand)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machine(3, out);

    EXPECT_EQ(machine.GetBallCount(), 3);

    machine.InsertQuarter();
    machine.TurnCrank();

    EXPECT_EQ(machine.GetBallCount(), 2);

    machine.InsertQuarter();
    machine.TurnCrank();

    EXPECT_EQ(machine.GetBallCount(), 1);

    machine.InsertQuarter();
    machine.TurnCrank();

    EXPECT_EQ(machine.GetBallCount(), 0);
}

TEST(CMultiGumballMachine, InsertGumballsCommand)
{
    std::ostringstream out;

    const with_state::CMultiGumballMachine machine(3, out);

    machine.InsertGumballs(3);

    EXPECT_EQ(machine.GetBallCount(), 6);
    EXPECT_EQ(out.str(), "You inserted a gumballs\n");
}