#pragma once

#include <memory>

#include "Menu.h"
#include "Machine/CMultiGumballMachine.h"

class CommandHandler
{
public:
    explicit CommandHandler(std::unique_ptr<with_state::CMultiGumballMachine> gumballMachine)
        : m_gumballMachine(std::move(gumballMachine))
    {
        m_menu.AddItem("InsertQuarter", "Adds a quarter in machine.", [this]() { InsertQuarter(); });
        m_menu.AddItem("EjectQuarter", "Ejects a quarter from machine.", [this]() { EjectQuarter(); });
        m_menu.AddItem("TurnCrank", "Turn crank.", [this] { TurnCrank(); });
        m_menu.AddItem("InsertGumballs", "Insert 5 gumballs.", [this] { InsertGumballs(); });
        m_menu.AddItem("Info", "Get info about machine.", [this] { Info(); });
        m_menu.AddItem("Exit", "Exit.", [this] { Exit(); });
    }

    void Run()
    {
        m_menu.Run();
    }

private:

    void InsertGumballs() const
    {
        m_gumballMachine->InsertGumballs(5);
    }

    void InsertQuarter() const
    {
        m_gumballMachine->InsertQuarter();
    }

    void EjectQuarter() const
    {
        m_gumballMachine->EjectQuarter();
    }

    void TurnCrank() const
    {
        m_gumballMachine->TurnCrank();
    }

    void Exit()
    {
        m_menu.Exit();
    }

    void Info() const
    {
        std::cout << m_gumballMachine->ToString();
    }

    Menu m_menu;
    std::unique_ptr<with_state::CMultiGumballMachine> m_gumballMachine;
};
