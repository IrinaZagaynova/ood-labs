#pragma once
#include "ICommandSink.h"
#include "History.h"

class CCommandSink : public ICommandSink
{
public:
	CCommandSink(CHistory& history)
		: m_history(history)
	{
	}
	void SaveCommand(std::unique_ptr<CAbstractCommand>&& command) override
	{
		m_history.AddAndExecuteCommand(move(command));
	}
private:
	CHistory& m_history;
};