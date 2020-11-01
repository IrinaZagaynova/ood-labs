#include "stdafx.h"
#include "../Editor/Commands.h"
#include "../Editor/Paragraph.h"

BOOST_AUTO_TEST_CASE(InsertItemCommand_test)
{
	CHistory history;
	auto historyAdapter = std::make_unique<CCommandSink>(history);
	std::shared_ptr<IParagraph> paragrephPtr = std::make_shared<CParagraph>(move(historyAdapter), "item");
	std::vector<CDocumentItem> items;
	CDocumentItem item(paragrephPtr);
	CInsertItemCommand command(items, item, 0);
	command.Execute();
	BOOST_CHECK_EQUAL(items.size(), 1);
	BOOST_CHECK_EQUAL(items[0].GetParagraph()->GetText(), "item");
	command.Unexecute();
	BOOST_CHECK_EQUAL(items.size(), 0);
}

BOOST_AUTO_TEST_CASE(DeleteItemCommand_test)
{
	CHistory history;
	auto historyAdapter = std::make_unique<CCommandSink>(history);
	std::shared_ptr<IParagraph> paragrephPtr = std::make_shared<CParagraph>(move(historyAdapter), "item");
	std::vector<CDocumentItem> items;
	CDocumentItem item(paragrephPtr);
	CInsertItemCommand insertCommand(items, item, 0);
	insertCommand.Execute();
	CDeleteItemCommand deleteCommand(items, 0);
	deleteCommand.Execute();
	BOOST_CHECK_EQUAL(items.size(), 0);
	deleteCommand.Unexecute();
	BOOST_CHECK_EQUAL(items.size(), 1);
	BOOST_CHECK_EQUAL(items[0].GetParagraph()->GetText(), "item");
}

BOOST_AUTO_TEST_CASE(ChangeStringCommand_test)
{
	std::string text = "item";
	CChangeStringCommand command(text, "new text");
	command.Execute();
	BOOST_CHECK_EQUAL(text, "new text");
	command.Unexecute();
	BOOST_CHECK_EQUAL(text, "item");
}

BOOST_AUTO_TEST_CASE(ResizeImageCommand_test)
{
	int width = 200;
	int height = 100;
	CResizeImageCommand command(width, height, 400, 200);
	command.Execute();
	BOOST_CHECK_EQUAL(width, 400);
	BOOST_CHECK_EQUAL(height, 200);
	command.Unexecute();
	BOOST_CHECK_EQUAL(width, 200);
	BOOST_CHECK_EQUAL(height, 100);
}