#include "stdafx.h"
#include "../Editor/Document.h"
#include <fstream>

struct EmptyDocumentFixture
{
	CDocument document;
};

BOOST_FIXTURE_TEST_SUITE(EmptyDocument, EmptyDocumentFixture)
	BOOST_AUTO_TEST_CASE(document_initialization_test)
	{
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		BOOST_CHECK(!document.CanUndo());
		BOOST_CHECK(!document.CanRedo());
	}
	
	BOOST_AUTO_TEST_SUITE(InsertParagraph_test)
		BOOST_AUTO_TEST_CASE(can_insert_paragraph)
		{
			BOOST_CHECK_EQUAL(document.InsertParagraph("firts").get(), document.GetItem(0).GetParagraph().get());
			BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "firts");
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		}
		BOOST_AUTO_TEST_CASE(cant_insert_paragraph_if_position_number_exceed_number_of_document_items)
		{
			BOOST_CHECK_THROW(document.InsertParagraph("item", 1), std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(InsertImage_test)
		BOOST_AUTO_TEST_CASE(can_insert_image)
		{
			BOOST_CHECK_EQUAL(document.InsertImage("test-image.jpg", 500, 300).get(), document.GetItem(0).GetImage().get());
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetPath().remove_filename(), std::filesystem::temp_directory_path());
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 500);
			BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 300);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		}
		BOOST_AUTO_TEST_CASE(cant_insert_nonexistent_image)
		{
			BOOST_CHECK_THROW(document.InsertImage("non-existent.jpg", 500, 300), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(cant_insert_image_if_position_number_exceed_number_of_document_items)
		{
			BOOST_CHECK_THROW(document.InsertImage("test-image.jpg", 500, 300, 1), std::out_of_range);
		}
		BOOST_AUTO_TEST_CASE(cant_insert_image_with_invalid_size)
		{
			BOOST_CHECK_THROW(document.InsertImage("test-image.jpg", 0, 300), std::invalid_argument);
			BOOST_CHECK_THROW(document.InsertImage("test-image.jpg", 500, 1001), std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_CASE(can_set_title)
	{
		document.SetTitle("title");
		BOOST_CHECK_EQUAL(document.GetTitle(), "title");
	}
	
	BOOST_AUTO_TEST_SUITE(DeleteItem_test)
		BOOST_AUTO_TEST_CASE(can_delete_item)
		{
			document.InsertParagraph("item");
			document.DeleteItem(0);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		}
		BOOST_AUTO_TEST_CASE(cant_delete_item_if_position_number_exceed_number_of_document_items)
		{
			BOOST_CHECK_THROW(document.DeleteItem(1), std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

struct when_non_empty_document_ : EmptyDocumentFixture
{
	when_non_empty_document_()
	{
		document.SetTitle("title");
		document.InsertParagraph("<>&\"'");
		document.InsertImage("test-image.jpg", 500, 300, 1);
	}
};

BOOST_FIXTURE_TEST_SUITE(when_non_empty_document, when_non_empty_document_)

	BOOST_AUTO_TEST_CASE(can_undo_and_redo_commands)
	{
		BOOST_CHECK(document.CanUndo());
		document.Undo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		BOOST_CHECK(document.CanUndo());
		document.Undo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		BOOST_CHECK(document.CanUndo());
		document.Undo();
		BOOST_CHECK_EQUAL(document.GetTitle(), "");
		BOOST_CHECK(!document.CanUndo());

		BOOST_CHECK(document.CanRedo());
		document.Redo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 0);
		BOOST_CHECK_EQUAL(document.GetTitle(), "title");
		BOOST_CHECK(document.CanRedo());
		document.Redo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		BOOST_CHECK(document.CanRedo());
		document.Redo();
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
		BOOST_CHECK(!document.CanRedo());
	}
	
	BOOST_AUTO_TEST_CASE(can_save_document)
	{
		Path path = std::filesystem::temp_directory_path() / "document";

		if (!std::filesystem::is_directory(path))
		{
			std::filesystem::create_directory(path);
		}

		document.Save(path);

		std::ifstream strm(path / "index.html");	
		std::string text, line;
		while (std::getline(strm, line))
		{
			text.append(line + "\n");
		}

		std::string expected = R"(<html>
<head>
<title>title</title>
</head>
<body>
<p>
&lt&gt&amp&quot&apos
</p>
<img src="./images/)" + document.GetItem(1).GetImage()->GetPath().filename().string() + R"("width="500"height="300"/>
</body>
</html>
)";

		BOOST_CHECK_EQUAL(text, expected);

		strm.close();
		if (std::filesystem::exists(path))
		{
			std::filesystem::remove_all(path);
		}
	}
BOOST_AUTO_TEST_SUITE_END()