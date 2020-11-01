#include "stdafx.h"
#include "MockCommandSink.h"
#include "../Editor/Paragraph.h"
#include <memory>

BOOST_AUTO_TEST_CASE(can_get_text)
{
	std::stringstream ostrm;
	std::unique_ptr<CMockCommandSink> commandSink = std::make_unique<CMockCommandSink>(ostrm);
	CParagraph paragraph(move(commandSink), "text");
	BOOST_CHECK_EQUAL(paragraph.GetText(), "text");
}

BOOST_AUTO_TEST_CASE(can_execute_command_when_setting_text)
{
	std::stringstream ostrm;
	std::unique_ptr<CMockCommandSink> commandSink = std::make_unique<CMockCommandSink>(ostrm);
	CParagraph paragraph(move(commandSink), "text");
	paragraph.SetText("");
	BOOST_CHECK_EQUAL(ostrm.str(), "command executed");
}