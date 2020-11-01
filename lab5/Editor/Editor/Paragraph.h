#pragma once
#include "IParagraph.h"
#include "History.h"
#include "Document.h"
#include "Commands.h"
#include "ICommandSink.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::unique_ptr<ICommandSink>&& commandSink, const std::string& text)
		: m_commandSink(move(commandSink))
		, m_text(text)
	{
	}
	std::string GetText() const override
	{
		return m_text;
	}
	void SetText(const std::string& text) override
	{
		m_commandSink->SaveCommand(move(std::make_unique<CChangeStringCommand>(m_text, text)));
	}

private:
	std::unique_ptr<ICommandSink> m_commandSink;
	std::string m_text;
};