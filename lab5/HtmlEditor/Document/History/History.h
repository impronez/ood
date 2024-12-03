#pragma once

#include <memory>
#include <vector>
#include "../Command/ICommand.h"

class History
{
public:
    [[nodiscard]] bool CanUndo() const
    {
        return m_currentActionIndex > 0;
    }

    [[nodiscard]] bool CanRedo() const
    {
        return m_currentActionIndex < m_commands.size();
    }

    void Undo()
    {
        if (CanUndo())
        {
            std::cout << "Undo before:" << m_currentActionIndex << std::endl;
            m_commands[--m_currentActionIndex]->Unexecute();
            std::cout << "Undo after:" << m_currentActionIndex << std::endl;
        }
    }

    void Redo()
    {
        if (CanRedo())
        {
            std::cout << "Redo before:" << m_currentActionIndex << std::endl;
            m_commands[m_currentActionIndex++]->Execute();
            std::cout << "Redo after:" << m_currentActionIndex << std::endl;
        }
    }

    void AddAndExecute(std::unique_ptr<ICommand> command, bool isMergeable = false)
    {
        if (m_currentActionIndex < m_commands.size())
        {
            for (size_t i = m_currentActionIndex; i < m_commands.size(); ++i)
            {
                m_commands[i]->Destroy();
            }
            m_commands.erase(m_commands.begin() + m_currentActionIndex, m_commands.end());
        }

        if (isMergeable && !m_commands.empty() && m_commands.back().get()->Merge(*command))
        {}
        else
        {
            command->Execute();
            m_commands.emplace_back(std::move(command));
            m_currentActionIndex++;
        }

        if (m_commands.size() > MAX_COMMANDS_COUNT)
        {
            m_commands.erase(m_commands.begin());
        }

        std::cout << "Successfully!\n";
    }

    void Clear()
    {
        for (const auto& command: m_commands)
        {
            command->Destroy();
        }
        m_commands.clear();
    }

private:
    static constexpr unsigned MAX_COMMANDS_COUNT = 10;
    std::vector<std::unique_ptr<ICommand> > m_commands;
    unsigned m_currentActionIndex = 0;
};