#include "EncryptOutputStream.h"
#include <algorithm>
#include <random>
#include <numeric>

CEncryptOutputStream::CEncryptOutputStream(std::unique_ptr<IOutputDataStream>&& stream, size_t key)
	: COutputStreamDecorator(move(stream)), m_enctyptTable(256)
{
	std::iota(m_enctyptTable.begin(), m_enctyptTable.end(), 0);
	std::shuffle(m_enctyptTable.begin(), m_enctyptTable.end(), std::mt19937(key));	
}

void CEncryptOutputStream::WriteByte(uint8_t data)
{
	m_stream->WriteByte(m_enctyptTable[data]);
}

void CEncryptOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	auto data = static_cast<const uint8_t*>(srcData);

	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(*data++);
	}
}
