#pragma once

#include <memory>

class ICommand
{
public:
    virtual void Execute() = 0;
    virtual void Unexecute() = 0;
    virtual bool Merge(const ICommand& other) = 0;
    virtual void Destroy() = 0;

    virtual ~ICommand() = default;
};

typedef std::unique_ptr<ICommand> ICommandPtr;