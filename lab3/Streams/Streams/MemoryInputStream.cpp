#include "MemoryInputStream.h"
#include <iostream>

ÑMemoryInputStream::ÑMemoryInputStream(std::vector<uint8_t>& data)
    : m_data(data)
{
}

bool ÑMemoryInputStream::IsEOF() const
{
    return m_position == m_data.size();
}

uint8_t ÑMemoryInputStream::ReadByte()
{
    if (IsEOF())
    {
        throw std::ios_base::failure("Error reading data from stream");
    }

    return m_data[unsigned(m_position++)];   
}

std::streamsize ÑMemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
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