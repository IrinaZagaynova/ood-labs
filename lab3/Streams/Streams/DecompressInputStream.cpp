#include "DecompressInputStream.h"
#include <iostream>

CDecompressInputStream::CDecompressInputStream(std::unique_ptr<IInputDataStream>&& stream)
    : CInputStreamDecorator(move(stream))
{
}

bool CDecompressInputStream::IsEOF() const
{
    return m_counter == 0 && m_stream->IsEOF();
}

uint8_t CDecompressInputStream::ReadByte()
{
    if (m_counter == 0)
    {
        m_counter = m_stream->ReadByte();
        if (m_stream->IsEOF())
        { 
            throw std::ios_base::failure("Data has an odd number of chars");
        }
        m_value = m_stream->ReadByte();
    }
    m_counter--;
    return m_value;
}

std::streamsize CDecompressInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
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
