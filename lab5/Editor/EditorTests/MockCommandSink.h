#pragma once
#include "../Editor/ICommandSink.h"
#include <sstream>

class CMockCommandSink : public ICommandSink
{
public:
	CMockCommandSink(std::ostream& strm)
		: m_strm(strm)
	{
	}
	void SaveCommand(std::unique_ptr<CAbstractCommand>&& command) override
	{
		m_strm << "command executed";
	}
private:
	std::ostream& m_strm;;
};