#include "stdafx.h"
#include "../Editor/Editor.h"

const std::string INSTRUCTION = R"(Commands list:
  help: Help
  exit: Exit
  setTitle: Changes title. Args: <new title>
  list: Show document
  insertParagraph: Insert Paragraph. Args: <position, text>
  insertImage: Insert Image. Args: <position, width, height, path>
  replaceText: Replace Text. Args: <position, new text>
  resizeImage: Resize Image. Args: <position, width, height>
  deleteItem: Delete Item. Args: <position>
  save: Save. Args: <path>
  undo: Undo command
  redo: Redo undone command
)";

struct EditorDependencies
{
	stringstream input;
	stringstream output;
};

struct EditorFixture : EditorDependencies
{
	CEditor editor;

	EditorFixture()
		: editor(input, output)
	{
	}

	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		input = stringstream();
		output = stringstream();
		BOOST_CHECK(input << command);
		editor.Start();
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_AUTO_TEST_CASE(Start_command_test)
{
	std::istringstream istrm;
	std::ostringstream ostrm;
	CEditor editor(istrm, ostrm);
	editor.Start();
	BOOST_CHECK_EQUAL(ostrm.str(), INSTRUCTION + '>');
}

BOOST_FIXTURE_TEST_SUITE(Editor, EditorFixture)

	BOOST_AUTO_TEST_CASE(Help_command_test)
	{
		VerifyCommandHandling("help", INSTRUCTION + '>' + INSTRUCTION + '>');
	}

	BOOST_AUTO_TEST_SUITE(insertParagraph_command_test)
		BOOST_AUTO_TEST_CASE(can_insert_paragraph)
		{
			std::string input = "insertParagraph end first\ninsertParagraph 0 second\ninsertParagraph 1 third\nlist";
			std::string expected = INSTRUCTION + R"(>>>>0. Paragraph:  second
1. Paragraph:  third
2. Paragraph:  first
>)";
			VerifyCommandHandling(input, expected);
		}
		BOOST_AUTO_TEST_CASE(can_undo_insertParagraph_command)
		{
			VerifyCommandHandling("insertParagraph end first\nundo\nlist", INSTRUCTION + ">>>>");
		}
		BOOST_AUTO_TEST_CASE(can_redo_insertParagraph_command)
		{
			VerifyCommandHandling("insertParagraph end first\nundo\nredo\nlist", INSTRUCTION + ">>>>0. Paragraph:  first\n>");
		}
		BOOST_AUTO_TEST_CASE(cant_insert_paragraph_if_given_position_isnt_number_or_end)
		{
			VerifyCommandHandling("insertParagraph position item\nlist", INSTRUCTION + ">invalid position\n>>");
		}
		BOOST_AUTO_TEST_CASE(cant_insert_paragraph_if_given_position_number_exceed_number_of_document_items)
		{
			VerifyCommandHandling("insertParagraph 1 item\nlist", INSTRUCTION + ">position number shouldn't exceed number of document items\n>>");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(insertImage_command_test)
		BOOST_AUTO_TEST_CASE(can_insert_image)
		{
			VerifyCommandHandling("insertImage end 500 300 test-image.jpg\n", INSTRUCTION + ">>");
		}
		BOOST_AUTO_TEST_CASE(can_undo_insertImage_command)
		{
			VerifyCommandHandling("insertImage end 500 300 test-image.jpg\nundo\nlist", INSTRUCTION + ">>>>");
		}
		BOOST_AUTO_TEST_CASE(can_redo_insertImage_command)
		{
			VerifyCommandHandling("insertImage end 500 300 test-image.jpg\nundo\nredo\n", INSTRUCTION + ">>>>");
		}
		BOOST_AUTO_TEST_CASE(cant_insert_nonexistent_image)
		{
			VerifyCommandHandling("insertImage end 500 300 non-existent.jpg\n", INSTRUCTION + ">given path doesn't exists\n>");
		}
		BOOST_AUTO_TEST_CASE(cant_insert_image_if_given_position_isnt_number_or_end)
		{
			VerifyCommandHandling("insertImage position 500 300 test-image.jpg\n", INSTRUCTION + ">invalid position\n>");
		}
		BOOST_AUTO_TEST_CASE(cant_insert_image_if_given_position_number_exceed_number_of_document_items)
		{
			std::string input = "insertImage 1 500 300 test-image.jpg\n";
			std::string expected = INSTRUCTION + ">position number shouldn't exceed number of document items\n>";
			VerifyCommandHandling(input, expected);
		}
		BOOST_AUTO_TEST_CASE(cant_insert_image_with_invalid_image_size)
		{
			std::string input = "insertImage end 0 500 test-image.jpg\ninsertImage end 500 1001 test-image.jpg\n";
			std::string expected = INSTRUCTION + ">invalid image sizes\n>invalid image sizes\n>";
			VerifyCommandHandling(input, expected);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(setTitle_command_test)
		BOOST_AUTO_TEST_CASE(can_set_title)
		{
			VerifyCommandHandling("setTitle title\nlist", INSTRUCTION + ">>Title: title\n>");
		}
		BOOST_AUTO_TEST_CASE(can_undo_setTitle_command)
		{
			VerifyCommandHandling("setTitle title\nundo\nlist", INSTRUCTION + ">>>>");
		}
		BOOST_AUTO_TEST_CASE(can_redo_setTitle_command)
		{
			VerifyCommandHandling("setTitle title\nundo\nredo\nlist", INSTRUCTION + ">>>>Title: title\n>");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(replaceText_command_test)
		BOOST_AUTO_TEST_CASE(can_replace_text)
		{
			std::string input = "insertParagraph end text\nreplaceText 0 newText\nlist";
			std::string expected = INSTRUCTION + ">>>0. Paragraph:  newText\n>";
			VerifyCommandHandling(input, expected);
		}
		BOOST_AUTO_TEST_CASE(can_undo_replace_text_command)
		{
			std::string input = "insertParagraph end text\nreplaceText 0 newText\nundo\nlist";
			std::string expected = INSTRUCTION + ">>>>0. Paragraph:  text\n>";
			VerifyCommandHandling(input, expected);
		}
		BOOST_AUTO_TEST_CASE(can_redo_replace_text_command)
		{
			std::string input = "insertParagraph end text\nreplaceText 0 newText\nundo\nredo\nlist";
			std::string expected = INSTRUCTION + ">>>>>0. Paragraph:  newText\n>";
			VerifyCommandHandling(input, expected);
		}
		BOOST_AUTO_TEST_CASE(cant_replace_text_if_given_position_isnt_number)
		{
			std::string input = "replaceText end newText\n";
			std::string expected = INSTRUCTION + ">invalid position\n>";
			VerifyCommandHandling(input, expected);
		}
		BOOST_AUTO_TEST_CASE(cant_replace_text_if_there_is_no_paragraph_in_given_position)
		{
			std::string input = "insertImage end 500 300 test-image.jpg\nreplaceText 0 newText\n";
			std::string expected = INSTRUCTION + ">>there is no paragraph in this position\n>";
			VerifyCommandHandling(input, expected);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(deleteItem_command_test)
		BOOST_AUTO_TEST_CASE(can_delete_item)
		{
			VerifyCommandHandling("insertParagraph end text\ndeleteItem 0\nlist", INSTRUCTION + ">>>>");
		}
		BOOST_AUTO_TEST_CASE(can_undo_DeleteItem_command)
		{
			std::string input = "insertParagraph end text\ndeleteItem 0\nundo\nlist";
			std::string expected = INSTRUCTION + ">>>>0. Paragraph:  text\n>";
			VerifyCommandHandling(input, expected);
		}
		BOOST_AUTO_TEST_CASE(can_redo_DeleteItem_command)
		{
			VerifyCommandHandling("insertParagraph end text\ndeleteItem 0\nundo\nredo\nlist", INSTRUCTION + ">>>>>>");
		}
		BOOST_AUTO_TEST_CASE(cant_delete_item_if_given_position_isnt_number)
		{
			VerifyCommandHandling("insertParagraph end text\ndeleteItem end\n", INSTRUCTION + ">>invalid position\n>");
		}
		BOOST_AUTO_TEST_CASE(cant_delete_item_if_there_are_no_items_in_given_position)
		{
			std::string input = "insertParagraph end text\ndeleteItem 1\n";
			std::string expected = INSTRUCTION + ">>position number shouldn't exceed number of document items\n>";
			VerifyCommandHandling(input, expected);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(save_command_test)
		BOOST_AUTO_TEST_CASE(can_save_document)
		{
			Path path = std::filesystem::temp_directory_path() / "document";

			if (!std::filesystem::is_directory(path))
			{
				std::filesystem::create_directory(path);
			}

			VerifyCommandHandling("save " + path.string(), INSTRUCTION + ">>");
			BOOST_CHECK(std::filesystem::exists(path / "images"));
			BOOST_CHECK(std::filesystem::exists(path / "index.html"));

			if (std::filesystem::exists(path))
			{
				std::filesystem::remove_all(path);
			}
		}
		BOOST_AUTO_TEST_CASE(cant_save_document_to_invalid_path)
		{
			VerifyCommandHandling("save invalidPath", INSTRUCTION + ">invalid path\n>");
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_CASE(undo_command_test)
	{
		VerifyCommandHandling("undo", INSTRUCTION + ">Can't undo\n>");
		VerifyCommandHandling("insertParagraph end text\nundo\nundo", INSTRUCTION + ">>>Can't undo\n>");
	}

	BOOST_AUTO_TEST_CASE(redo_command_test)
	{
		VerifyCommandHandling("redo", INSTRUCTION + ">Can't redo\n>");
		VerifyCommandHandling("insertParagraph end text\nundo\nredo\nredo", INSTRUCTION + ">>>>Can't redo\n>");
	}

BOOST_AUTO_TEST_SUITE_END()
