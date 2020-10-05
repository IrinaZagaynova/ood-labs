#include "../../../catch2/catch.hpp"
#include "../Streams/MemoryInputStream.h"

TEST_CASE("Can't read byte from empty vector")
{
	std::vector<uint8_t> data;
	СMemoryInputStream istrm(data);
	CHECK_THROWS_AS(istrm.ReadByte(), std::ios_base::failure);
}

TEST_CASE("Can read byte from memory stream")
{
	std::vector<uint8_t> data = {'a', 'b', 'c'};
	СMemoryInputStream istrm(data);

	CHECK(istrm.ReadByte() == 'a');
	CHECK(istrm.ReadByte() == 'b');
	CHECK(istrm.ReadByte() == 'c');
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

TEST_CASE("ReadBlock return the number of bytes actually read")
{
	uint8_t buffer[5];

	std::vector<uint8_t> empty = {};
	СMemoryInputStream istrm1(empty);
	CHECK(istrm1.ReadBlock(buffer, 5) == 0);

	std::vector<uint8_t> data = { 'a', 'b', 'c', 'd' };
	СMemoryInputStream istrm2(data);
	CHECK(istrm2.ReadBlock(buffer, 5) == 4);
}

TEST_CASE("IsEOF returns true if the last read operation from memory strem failed")
{
	std::vector<uint8_t> data = { 'a', 'b', 'c', 'd' };
	СMemoryInputStream istrm(data);
	uint8_t buffer[4];
	CHECK(istrm.ReadBlock(buffer, 4) == 4);
	CHECK_THROWS_AS(istrm.ReadByte(), std::ios_base::failure);
	CHECK(istrm.IsEOF());
}