#include "../../../catch2/catch.hpp"
#include "../Streams/OutputStreamDecorator.h"
#include "../Streams/MemoryOutputStream.h"
#include "../Streams/EncryptOutputStream.h"
#include "../Streams/InputStreamDecorator.h"
#include "../Streams/MemoryInputStream.h"
#include "../Streams/DecryptInputStream.h"

TEST_CASE("Can encrypt and decrypt stream reading bytes")
{
	std::vector<uint8_t> data;

	SECTION("Write data")
	{
		std::unique_ptr<IOutputDataStream> ostrm = std::make_unique<CEncryptOutputStream>(std::make_unique<CMemoryOutputStream>(data), 15);
		ostrm->WriteByte('a');
		ostrm->WriteByte('a');
		ostrm->WriteByte('a');
		ostrm->WriteByte('b');
		ostrm->WriteByte('c');
		ostrm->WriteByte('c');
	}

	std::unique_ptr<IInputDataStream> istrm = std::make_unique<CDecryptInputStream>(std::make_unique<ÑMemoryInputStream>(data), 15);
	
	CHECK(istrm->ReadByte() == 'a');
	CHECK(istrm->ReadByte() == 'a');
	CHECK(istrm->ReadByte() == 'a');
	CHECK(istrm->ReadByte() == 'b');
	CHECK(istrm->ReadByte() == 'c');
	CHECK(!istrm->IsEOF());
	CHECK(istrm->ReadByte() == 'c');
	CHECK(istrm->IsEOF());
}

TEST_CASE("Can encrypt and decrypt stream reading a block")
{
	std::vector<uint8_t> data;

	SECTION("Write data")
	{
		std::unique_ptr<IOutputDataStream> ostrm = std::make_unique<CEncryptOutputStream>(std::make_unique<CMemoryOutputStream>(data), 15);
		uint8_t srcData[] = { 'a', 'a', 'b', 'b', 'b', 'c', 'c', 'c' };
		ostrm->WriteBlock(srcData, 8);
	}

	std::unique_ptr<IInputDataStream> istrm = std::make_unique<CDecryptInputStream>(std::make_unique<ÑMemoryInputStream>(data), 15);
	uint8_t buffer[10];

	CHECK(istrm->ReadBlock(buffer, 10) == 8);
	uint8_t expected[8] = { 'a', 'a', 'b', 'b', 'b', 'c', 'c', 'c' };

	for (uint8_t i = 0; i < 8; i++)
	{
		CHECK(buffer[i] == expected[i]);
	}
	CHECK(istrm->IsEOF());
}

TEST_CASE("Can encrypt and decrypt a stream multiple times")
{
	std::vector<uint8_t> data;

	SECTION("Write data")
	{
		std::unique_ptr<IOutputDataStream> ostrm = 
			std::make_unique<CEncryptOutputStream>
				(std::make_unique<CEncryptOutputStream>
					(std::make_unique<CEncryptOutputStream>
						(std::make_unique<CMemoryOutputStream>(data), 
						15),
					150),
				424);


		uint8_t srcData[] = { 'a', 'a', 'b', 'b', 'b', 'c', 'c', 'c' };
		ostrm->WriteBlock(srcData, 8);
	}

	std::unique_ptr<IInputDataStream> istrm =
		std::make_unique<CDecryptInputStream>
		(std::make_unique<CDecryptInputStream>
			(std::make_unique<CDecryptInputStream>
				(std::make_unique<ÑMemoryInputStream>(data),
					15),
				150),
			424);

	uint8_t buffer[8];

	CHECK(istrm->ReadBlock(buffer, 8) == 8);
	uint8_t expected[8] = { 'a', 'a', 'b', 'b', 'b', 'c', 'c', 'c' };
	for (uint8_t i = 0; i < 8; i++)
	{
		CHECK(buffer[i] == expected[i]);
	}
}