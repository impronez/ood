#pragma once
#include "CCommand.h"

class SetTitleCommand : public CCommand
{
public:
    explicit SetTitleCommand(std::string& title, const std::string& newTitle)
        : m_currentTitle(title),
        m_newTitle(newTitle)
    {}

    void DoExecute() override
    {
        std::swap(m_currentTitle, m_newTitle);
    }

    void DoUnexecute() override
    {
        std::swap(m_newTitle, m_currentTitle);
    }

    bool Merge(const ICommand& other) override
    {
        if (const auto replaceCmd = dynamic_cast<const SetTitleCommand*>(&other))
        {
            m_currentTitle = replaceCmd->m_newTitle;

            return true;
        }
        else
        {
            return false;
        }
    }

    void Destroy() override
    {}

private:
    std::string &m_currentTitle;
    std::string m_newTitle;
};