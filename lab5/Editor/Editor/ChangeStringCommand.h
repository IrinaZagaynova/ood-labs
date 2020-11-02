#pragma once
#include "AbstractCommand.h"
#include <string>

class CChangeStringCommand : public CAbstractCommand
{
public:
	CChangeStringCommand(std::string& target, std::string const& newValue)
		: m_target(target)
		, m_newValue(newValue)
	{
	}

protected:
	void DoExecute() override
	{
		m_newValue.swap(m_target);
	}
	void DoUnexecute() override
	{
		m_newValue.swap(m_target);
	}

private:
	std::string m_newValue;
	std::string& m_target;
};