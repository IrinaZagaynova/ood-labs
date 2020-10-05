#include "FileOutputStream.h"
#include <iostream>

CFileOutputStream::CFileOutputStream(const std::string& fileName)
{
	m_stream.open(fileName, std::ios_base::binary);
	if (!m_stream.is_open())
	{
		throw std::ios_base::failure(fileName + " not found");
	}
}

void CFileOutputStream::WriteByte(uint8_t data)
{
	if (!m_stream.put(data))
	{
		throw std::ios_base::failure("Error writing to file");
	}
}

void CFileOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	auto data = static_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(*data++);
	}
}
