#include "stdafx.h"
#include "../Editor/Document.h"

BOOST_AUTO_TEST_CASE(can_undo_only_ten_commands)
{
	CDocument document;
	for (size_t i = 0; i < 11; i++)
	{
		document.SetTitle(std::to_string(i));
	}

	for (size_t i = 0; i < 10; i++)
	{
		BOOST_CHECK(document.CanUndo());
		document.Undo();
	}

	BOOST_CHECK(!document.CanUndo());
}
BOOST_AUTO_TEST_CASE(should_remove_unexecuted_commands_when_inserting_new_ones)
{
	CDocument document;
	for (size_t i = 0; i < 3; i++)
	{
		document.SetTitle(std::to_string(i));
	}

	document.Undo();
	document.Undo();

	document.SetTitle("title");
	document.Undo();
	document.Redo();

	BOOST_CHECK(!document.CanRedo());
}
