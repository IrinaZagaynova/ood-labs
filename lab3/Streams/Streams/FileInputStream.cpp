#include "FileInputStream.h"
#include <iostream>

CFileInputStream::CFileInputStream(const std::string& fileName)
{
	m_stream.open(fileName, std::ios_base::binary);
	if (!m_stream.is_open())
	{
		throw std::ios_base::failure(fileName + " not found");
	}
}

bool CFileInputStream::IsEOF() const
{
	return m_stream.eof();
}

uint8_t CFileInputStream::ReadByte()
{	
	char byte;
	m_stream.get(byte);

	if (IsEOF())
	{
		throw std::ios_base::failure("Error reading from file");
	}

	return (uint8_t)byte;
}

std::streamsize CFileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto buffer = static_cast<uint8_t*>(dstBuffer);
	std::streamsize bytesCouter = 0;
	for (bytesCouter = 0; bytesCouter < size; bytesCouter++)
	{
		if (IsEOF())
		{
			break;
		}
		*buffer++ = ReadByte();
	}

	return bytesCouter;
}
