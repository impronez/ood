#include <gtest/gtest.h>

#include "../Machine/CNaiveMultiGumballMachine.h"

namespace
{
    std::string GetMachineState(unsigned count, const std::string& state)
    {
        return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)",
            count,
            (count != 1 ? "s" : ""),
            state
        );
    }
}

TEST(CNaiveMultiGumballMachine, InitializeTest)
{
    std::ostringstream out;

    naive::CNaiveMultiGumballMachine machineWithGumb(5, out);
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(5, "waiting for quarter"));

    naive::CNaiveMultiGumballMachine machineWithoutGumb(0, out);
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));
}

TEST(CNaiveMultiGumballMachine, InsertQuarterCommand)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machineWithoutGumb(0, out);

    machineWithoutGumb.InsertQuarter();
    EXPECT_EQ(out.str(), "You can't insert a quarter, the machine is sold out\n");
    EXPECT_EQ(machineWithoutGumb.ToString(), GetMachineState(0, "sold out"));

    naive::CNaiveMultiGumballMachine machineWithGumb(5, out);
    machineWithGumb.InsertQuarter();

    EXPECT_EQ(out.str(), "You can't insert a quarter, the machine is sold out\nYou inserted a quarter\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(5, "waiting for turn of crank"));

    out.str("");
    machineWithGumb.InsertQuarter();

    EXPECT_EQ(out.str(), "You inserted a quarter\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(5, "waiting for turn of crank"));
}

TEST(CNaiveMultiGumballMachine, EjectQuarterCommand)
{
    std::ostringstream out;

    naive::CNaiveMultiGumballMachine machineWithoutGumb(0, out);
    machineWithoutGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "You can't eject, you haven't inserted a quarter yet\n");

    out.str("");

    naive::CNaiveMultiGumballMachine machineWithGumb(5, out);
    machineWithGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "You haven't inserted a quarter\n");

    machineWithGumb.InsertQuarter();
    out.str("");
    machineWithGumb.EjectQuarter();

    EXPECT_EQ(out.str(), "Quarter returned\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(5, "waiting for quarter"));
}

TEST(CNaiveMultiGumballMachine, TurnCrankCommand)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machineWithoutGumb(0, out);

    machineWithoutGumb.TurnCrank();
    EXPECT_EQ(out.str(), "You turned but there's no gumballs\n");

    out.str("");

    naive::CNaiveMultiGumballMachine machineWithGumb(5, out);
    machineWithGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned but there's no quarter\n");

    machineWithGumb.InsertQuarter();
    out.str("");
    machineWithGumb.TurnCrank();

    EXPECT_EQ(out.str(), "You turned...\nA gumball comes rolling out the slot\n");
    EXPECT_EQ(machineWithGumb.ToString(), GetMachineState(4, "waiting for quarter"));
}

TEST(CNaiveMultiGumballMachine, RefillCommand)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machine(1, out);

    machine.Refill(0);
    EXPECT_EQ(machine.ToString(), GetMachineState(0, "sold out"));

    machine.Refill(1);
    EXPECT_EQ(machine.ToString(), GetMachineState(1, "waiting for quarter"));
}

TEST(CNaiveMultiGumballMachine, AddQuarterCommand)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machine(0, out);

    EXPECT_EQ(machine.ToString(), GetMachineState(0, "sold out"));

    machine.AddQuarter();
    EXPECT_EQ(out.str(), "You inserted a quarter\n");
    EXPECT_EQ(machine.GetQuarterCount(), 1);

    machine.AddQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 2);

    machine.AddQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 3);

    machine.AddQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 4);

    machine.AddQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 5);

    machine.AddQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 5);
}

TEST(CNaiveMultiGumballMachine, ReleaseAllQuartersCommand)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machine(0, out);

    machine.ReleaseAllQuarters();
    EXPECT_EQ(machine.ToString(), GetMachineState(0, "waiting for quarter"));
    EXPECT_EQ(machine.GetQuarterCount(), 0);

    machine.Refill(3);
    machine.InsertQuarter();
    machine.InsertQuarter();
    machine.InsertQuarter();

    EXPECT_EQ(machine.GetQuarterCount(), 3);

    machine.ReleaseAllQuarters();
    EXPECT_EQ(machine.GetQuarterCount(), 0);
    EXPECT_EQ(machine.ToString(), GetMachineState(3, "waiting for quarter"));
}

TEST(CNaiveMultiGumballMachine, TakeQuarterCommand)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machine(3, out);

    machine.TakeQuarter();
    EXPECT_EQ(machine.GetQuarterCount(), 0);
    EXPECT_EQ(machine.ToString(), GetMachineState(3, "waiting for quarter"));

    machine.Refill(0);
    machine.TakeQuarter();
    EXPECT_EQ(machine.ToString(), GetMachineState(0, "sold out"));

    machine.Refill(3);
    machine.TakeQuarter();
    EXPECT_EQ(machine.ToString(), GetMachineState(3, "waiting for quarter"));
}

TEST(CNaiveMultiGumballMachine, ReleaseBallCommand)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machine(3, out);

    machine.ReleaseBall();
    EXPECT_EQ(machine.GetGumballCount(), 2);
    EXPECT_EQ(machine.ToString(), GetMachineState(2, "waiting for quarter"));

    machine.InsertQuarter();
    machine.ReleaseBall();
    EXPECT_EQ(machine.GetGumballCount(), 1);
    EXPECT_EQ(machine.ToString(), GetMachineState(1, "waiting for turn of crank"));

    machine.ReleaseBall();
    EXPECT_EQ(machine.GetGumballCount(), 0);
    EXPECT_EQ(machine.ToString(), GetMachineState(0, "sold out"));
}

TEST(CNaiveMultiGumballMachine, SoldStateTest)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machine(5, out);

    naive::IGumballMachine* machinePtr = &machine;

    machinePtr->SetSoldState();
    machine.InsertQuarter();
    EXPECT_EQ(out.str(), "Please wait, we're already giving you a gumball\n");
    EXPECT_EQ(machine.ToString(), GetMachineState(5, "delivering a gumball"));

    out.str("");
    machinePtr->SetSoldState();
    machine.EjectQuarter();

    EXPECT_EQ(out.str(), "Sorry you already turned the crank\n");

    out.str("");
    machine.TurnCrank();

    EXPECT_EQ(out.str(), "Turning twice doesn't get you another gumball\n");

    machinePtr->SetSoldState();
    out.str("");

    machinePtr->Dispense();
    EXPECT_EQ(out.str(), "A gumball comes rolling out the slot\n");
    EXPECT_EQ(machine.ToString(), GetMachineState(4, "waiting for quarter"));

    machine.Refill(1);
    machinePtr->SetSoldState();
    out.str("");
}

TEST(CNaiveMultiGumballMachine, DispenseCommand)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machine(1, out);
    naive::IGumballMachine* machinePtr = &machine;

    machinePtr->SetSoldState();
    machinePtr->Dispense();
    EXPECT_EQ(out.str(), "A gumball comes rolling out the slot\nOops, out of gumballs\n");
    EXPECT_EQ(machine.ToString(), GetMachineState(0, "sold out"));

    machinePtr->SetHasQuarterState();
    out.str("");
    machinePtr->Dispense();

    EXPECT_EQ(out.str(), "No gumball dispensed\n");

    machinePtr->SetSoldOutState();
    out.str("");
    machinePtr->Dispense();

    EXPECT_EQ(out.str(), "No gumball dispensed\n");

    machinePtr->SetNoQuarterState();
    out.str("");
    machinePtr->Dispense();

    EXPECT_EQ(out.str(), "You need to pay first\n");
}

TEST(CNaiveMultiGumballMachine, SetStateTest)
{
    std::ostringstream out;
    naive::CNaiveMultiGumballMachine machine(5, out);

    naive::IGumballMachine* machinePtr = &machine;

    machinePtr->SetSoldState();
    EXPECT_EQ(machine.ToString(), GetMachineState(5, "delivering a gumball"));

    machinePtr->SetHasQuarterState();
    EXPECT_EQ(machine.ToString(), GetMachineState(5, "waiting for turn of crank"));

    machinePtr->SetSoldOutState();
    EXPECT_EQ(machine.ToString(), GetMachineState(5, "sold out"));

    machinePtr->SetNoQuarterState();
    EXPECT_EQ(machine.ToString(), GetMachineState(5, "waiting for quarter"));
}