#include "../../../catch2/catch.hpp"
#include "../Streams/FileOutputStream.h"

std::string GetDataFromFile(const std::string& fileName)
{
	std::ifstream istrm(fileName);
	std::string str;
	char ch;

	while (istrm.get(ch))
	{
		str.push_back(ch);
	}

	return str;
}

TEST_CASE("Can write byte to file")
{
	SECTION("Write to file")
	{
		CFileOutputStream ostrm("output.bin");
		ostrm.WriteByte('a');
		ostrm.WriteByte('b');
		ostrm.WriteByte('1');
	}

	CHECK(GetDataFromFile("output.bin") == "ab1");
}

TEST_CASE("Can write block to file")
{
	SECTION("Write to file")
	{
		CFileOutputStream ostrm("output.bin");
		ostrm.WriteBlock("abc1a", 4);
	}

	CHECK(GetDataFromFile("output.bin") == "abc1");
}