#include "../../../catch2/catch.hpp"
#include "../Streams/FileInputStream.h"

TEST_CASE("Can't read byte from empty file")
{
	CFileInputStream istrm("empty.txt");
	CHECK(istrm.IsEOF());
	CHECK_THROWS_AS(istrm.ReadByte(), std::ios_base::failure);
}

TEST_CASE("Can read byte from file")
{
	CFileInputStream istrm("input.txt");
	CHECK(istrm.ReadByte() == 'a');
	CHECK(istrm.ReadByte() == 'b');
	CHECK(istrm.ReadByte() == 'c');
	CHECK(!istrm.IsEOF());
	CHECK(istrm.ReadByte() == '1');
	CHECK(istrm.IsEOF());
}

TEST_CASE("Can read block from file")
{
	CFileInputStream istrm("input.txt");
	uint8_t buffer[3];

	CHECK(istrm.ReadBlock(buffer, 3) == 3);
	CHECK(buffer[0] == 'a');
	CHECK(buffer[1] == 'b');
	CHECK(buffer[2] == 'c');
	CHECK(!istrm.IsEOF());

	CHECK(istrm.ReadBlock(buffer, 2) == 1);
	CHECK(buffer[0] == '1');
	CHECK(istrm.IsEOF());
}