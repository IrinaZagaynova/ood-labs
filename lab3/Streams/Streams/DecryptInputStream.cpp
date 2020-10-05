#include "DecryptInputStream.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <numeric>

CDecryptInputStream::CDecryptInputStream(std::unique_ptr<IInputDataStream>&& stream, size_t key)
    : CInputStreamDecorator(move(stream)), m_dectyptTable(256)
{
    std::vector<uint8_t> enctyptTable(256);
    std::iota(enctyptTable.begin(), enctyptTable.end(), 0);
    std::shuffle(enctyptTable.begin(), enctyptTable.end(), std::mt19937((unsigned int)key));
    for (size_t i = 0; i < 256; i++)
    {
        m_dectyptTable[enctyptTable[i]] = (uint8_t)i;
    }
}

bool CDecryptInputStream::IsEOF() const
{
    return m_stream->IsEOF();
}

uint8_t CDecryptInputStream::ReadByte()
{
    return m_dectyptTable[m_stream->ReadByte()];
}

std::streamsize CDecryptInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
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
