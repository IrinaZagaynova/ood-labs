#include "MemoryOutputStream.h"
#include <iostream>

CMemoryOutputStream::CMemoryOutputStream(std::vector<uint8_t>& data)
	: m_data(data)
{
}

void CMemoryOutputStream::WriteByte(uint8_t data)
{
	if (m_data.size() == m_data.max_size())
	{
		throw std::ios_base::failure("Error writing data to stream");
	}
	m_data.push_back(data);
}

void CMemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	auto data = static_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(*data++);
	}
}
