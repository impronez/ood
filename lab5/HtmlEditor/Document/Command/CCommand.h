#pragma once
#include "ICommand.h"

class CCommand : public ICommand
{
public:
    void Execute() override
    {
        if (!m_isExecuted)
        {
            DoExecute();
            m_isExecuted = true;
        }
    }

    void Unexecute() override
    {
        if (m_isExecuted)
        {
            DoUnexecute();
            m_isExecuted = false;
        }
    }

protected:
    virtual void DoExecute() = 0;
    virtual void DoUnexecute() = 0;

private:
    bool m_isExecuted = false;
};