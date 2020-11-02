#pragma once
#include "ICommand.h"
#include <vector>
#include <memory>

typedef std::unique_ptr<ICommand> ICommandPtr;

class CHistory
{
public:
	CHistory();
	~CHistory();

	bool CanUndo()const;
	void Undo();
	bool CanRedo()const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr&& command);
private:
	std::vector<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};