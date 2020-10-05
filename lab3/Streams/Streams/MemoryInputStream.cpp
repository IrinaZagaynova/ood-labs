#include "MemoryInputStream.h"
#include <iostream>

�MemoryInputStream::�MemoryInputStream(std::vector<uint8_t>& data)
    : m_data(data)
{
}

bool �MemoryInputStream::IsEOF() const
{
    return m_position == m_data.size();
}

uint8_t �MemoryInputStream::ReadByte()
{
    if (IsEOF())
    {
        throw std::ios_base::failure("Error reading data from stream");
    }

    return m_data[unsigned(m_position++)];   
}

std::streamsize �MemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto buffer = static_cast<uint8_t*>(dstBuffer);
	for (std::streamsize i = 0; i < size; i++)
	{
		try
		{
			*buffer++ = ReadByte();
		}
		catch (const std::ios_base::failure&)
		{
			return i;
		}
	}

	return size;
}