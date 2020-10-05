#include "../../../catch2/catch.hpp"
#include "../Streams/MemoryInputStream.h"

TEST_CASE("Can't read byte from empty vector")
{
	std::vector<uint8_t> data;
	СMemoryInputStream istrm(data);
	CHECK(istrm.IsEOF());
	CHECK_THROWS_AS(istrm.ReadByte(), std::ios_base::failure);
}

TEST_CASE("Can read byte from memory stream")
{
	std::vector<uint8_t> data = {'a', 'b', 'c'};
	СMemoryInputStream istrm(data);

	CHECK(istrm.ReadByte() == 'a');
	CHECK(istrm.ReadByte() == 'b');
	CHECK(!istrm.IsEOF());
	CHECK(istrm.ReadByte() == 'c');
	CHECK(istrm.IsEOF());
	CHECK_THROWS_AS(istrm.ReadByte(), std::ios::failure);
}

TEST_CASE("Can read block from memory stream")
{
	std::vector<uint8_t> data = { 'a', 'b', 'c', 1 , 2 };
	СMemoryInputStream istrm(data);
	uint8_t buffer[3];

	CHECK(istrm.ReadBlock(buffer, 3) == 3);

	CHECK(buffer[0] == 'a');
	CHECK(buffer[1] == 'b');
	CHECK(buffer[2] == 'c');
	CHECK(!istrm.IsEOF());

	CHECK(istrm.ReadBlock(buffer, 4) == 2);

	CHECK(buffer[0] == 1);
	CHECK(buffer[1] == 2);
	CHECK(istrm.IsEOF());
}
