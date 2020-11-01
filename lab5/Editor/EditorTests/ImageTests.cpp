#include "stdafx.h"
#include "MockCommandSink.h"
#include "../Editor/Image.h"
#include <memory>

BOOST_AUTO_TEST_CASE(can_get_image_params)
{
	std::stringstream ostrm;
	std::unique_ptr<CMockCommandSink> commandSink = std::make_unique<CMockCommandSink>(ostrm);
	CImage image(move(commandSink), "test-image.jpg" , 500, 300);
	BOOST_CHECK_EQUAL(image.GetPath().remove_filename(), std::filesystem::temp_directory_path());
	BOOST_CHECK_EQUAL(image.GetWidth(), 500);
	BOOST_CHECK_EQUAL(image.GetHeight(), 300);
}

BOOST_AUTO_TEST_CASE(can_execute_command_when_resizing_image)
{
	std::stringstream ostrm;
	std::unique_ptr<CMockCommandSink> commandSink = std::make_unique<CMockCommandSink>(ostrm);
	CImage image(move(commandSink), "test-image.jpg", 500, 300);
	image.Resize(100, 100);
	BOOST_CHECK_EQUAL(ostrm.str(), "command executed");
}