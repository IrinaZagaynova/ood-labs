#pragma once
#include "AbstractCommand.h"
#include <memory>

class ICommandSink
{
public:
    virtual ~ICommandSink() = default;
    virtual void SaveCommand(std::unique_ptr<CAbstractCommand>&& command) = 0;
};
