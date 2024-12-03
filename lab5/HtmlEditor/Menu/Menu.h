#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

class Menu
{
public:
    using Command = std::function<void(std::istringstream &)>;

    void AddItem(const std::string &shortcut, const std::string &desc, const Command &cmd)
    {
        m_items.emplace_back(shortcut, desc, cmd);
    }

    void Run()
    {
        ShowInstructions();

        std::string command;

        while (!m_exit && std::getline(std::cin, command))
        {
            try
            {
                ExecuteCommand(command);

                std::cout << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }

    void ShowInstructions() const
    {
        std::cout << "Commands:\n";
        for (const auto &item : m_items)
        {
            std::cout << '\t' << item.shortcut << ". " << item.description << std::endl;
        }
    }

    void Exit()
    {
        m_exit = true;
    }
private:

    void ExecuteCommand(const std::string &command)
    {
        std::istringstream iss(command);

        std::string name;
        iss >> name;

        const auto iter = std::ranges::find_if(m_items, [&name](const Item& item)
        {
            return item.shortcut == name;
        });

        if (iter == m_items.end())
        {
            throw std::invalid_argument("Unknown command " + name);
        }

        iter->command(iss);
    }

    struct Item
    {
        Item(std::string shortcut, std::string description, Command command)
            : shortcut(std::move(shortcut)),
            description(std::move(description)),
            command(std::move(command))
        {}

        std::string shortcut;
        std::string description;
        Command command;
    };

    std::vector<Item> m_items;
    bool m_exit = false;
};
