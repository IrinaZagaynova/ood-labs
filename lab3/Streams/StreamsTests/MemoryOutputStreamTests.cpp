#include "../../../catch2/catch.hpp"
#include "../Streams/MemoryOutputStream.h"

TEST_CASE("Can write byte to memory stream")
{
	std::vector<uint8_t> data;
	CMemoryOutputStream ostrm(data);

	ostrm.WriteByte('a');
	ostrm.WriteByte('b');
	ostrm.WriteByte('c');

	CHECK(data == std::vector<uint8_t>{'a', 'b', 'c'});
}

TEST_CASE("Can write block to memory stream")
{
	std::vector<uint8_t> data;
	CMemoryOutputStream ostrm(data);

	uint8_t srcData[] = { 'a', 'b', 1, 2, 3 } ;

	ostrm.WriteBlock(srcData, 4);
	CHECK(data == std::vector<uint8_t>{ 'a', 'b', 1, 2 });
}