#include "../../../catch2/catch.hpp"
#include "../Streams/OutputStreamDecorator.h"
#include "../Streams/CompressOutputStream.h"
#include "../Streams/MemoryOutputStream.h"
#include "../Streams/InputStreamDecorator.h"
#include "../Streams/DecompressInputStream.h"
#include "../Streams/MemoryInputStream.h"

TEST_CASE("Can compress and decompress stream by reading bytes")
{
	std::vector<uint8_t> data;

	SECTION("Write data")
	{
		std::unique_ptr<IOutputDataStream> ostrm = std::make_unique<CCompressOutputStream>(std::make_unique<CMemoryOutputStream>(data));
		ostrm->WriteByte('a');
		ostrm->WriteByte('a');
		ostrm->WriteByte('a');
		ostrm->WriteByte('b');
		ostrm->WriteByte('c');
		ostrm->WriteByte('c');
	}

	CHECK(data == std::vector<uint8_t>{3, 'a', 1, 'b', 2, 'c'});

	std::unique_ptr<IInputDataStream> istrm = std::make_unique<CDecompressInputStream>(std::make_unique<ÑMemoryInputStream>(data));
	
	CHECK(istrm->ReadByte() == 'a');
	CHECK(istrm->ReadByte() == 'a');
	CHECK(istrm->ReadByte() == 'a');
	CHECK(istrm->ReadByte() == 'b');
	CHECK(istrm->ReadByte() == 'c');
	CHECK(!istrm->IsEOF());
	CHECK(istrm->ReadByte() == 'c');
	CHECK(istrm->IsEOF());
}

TEST_CASE("Can compress and decompress stream by reading a block")
{
	std::vector<uint8_t> data;

	SECTION("Write data")
	{
		std::unique_ptr<IOutputDataStream> ostrm = std::make_unique<CCompressOutputStream>(std::make_unique<CMemoryOutputStream>(data));
		uint8_t srcData[] = { 'a', 'a', 'a', 'b', 'c', 'c'};
		ostrm->WriteBlock(srcData, 6);
	}

	CHECK(data == std::vector<uint8_t>{3, 'a', 1, 'b', 2, 'c'});

	std::unique_ptr<IInputDataStream> istrm = std::make_unique<CDecompressInputStream>(std::make_unique<ÑMemoryInputStream>(data));
	uint8_t buffer[10];

	CHECK(istrm->ReadBlock(buffer, 10) == 6);
	uint8_t expected[6] = { 'a', 'a', 'a', 'b', 'c', 'c' };

	for (uint8_t i = 0; i < 6; i++)
	{
		CHECK(buffer[i] == expected[i]);
	}
	CHECK(istrm->IsEOF());
}

TEST_CASE("Should throw an exception when trying to decompress an odd number of chars")
{
	std::vector<uint8_t> data;

	SECTION("Write data")
	{
		CMemoryOutputStream ostrm(data);
		uint8_t srcData[] = { 3, 'a', 2, 'b', 1 };
		ostrm.WriteBlock(srcData, 5);
	}

	std::unique_ptr<IInputDataStream> istrm = std::make_unique<CDecompressInputStream>(std::make_unique<ÑMemoryInputStream>(data));
	uint8_t buffer[6];
	CHECK_THROWS_AS(istrm->ReadBlock(buffer, 6), std::ios_base::failure);
}