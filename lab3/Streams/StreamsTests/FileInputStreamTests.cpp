#include "../../../catch2/catch.hpp"
#include "../Streams/FileInputStream.h"

TEST_CASE("Can't read byte from empty file")
{
	CFileInputStream istrm("empty.txt");
	CHECK_THROWS_AS(istrm.ReadByte(), std::ios_base::failure);
}

TEST_CASE("Can read byte from file")
{
	CFileInputStream istrm("input.txt");
	CHECK(istrm.ReadByte() == 'a');
	CHECK(istrm.ReadByte() == 'b');
	CHECK(istrm.ReadByte() == 'c');
	CHECK(istrm.ReadByte() == '1');
}

TEST_CASE("Can read block from file")
{
	CFileInputStream istrm("input.txt");
	uint8_t buffer[4];

	CHECK(istrm.ReadBlock(buffer, 4) == 4);
	CHECK(buffer[0] == 'a');
	CHECK(buffer[1] == 'b');
	CHECK(buffer[2] == 'c');
	CHECK(buffer[3] == '1');
}

TEST_CASE("IsEOF returns true if the last read operation failed")
{
	CFileInputStream istrm("input.txt");
	uint8_t buffer[3];
	CHECK(istrm.ReadBlock(buffer, 4) == 4);
	CHECK_THROWS_AS(istrm.ReadByte(), std::ios_base::failure);
	CHECK(istrm.IsEOF());
}