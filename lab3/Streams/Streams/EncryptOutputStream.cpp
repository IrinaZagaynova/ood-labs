#include "EncryptOutputStream.h"
#include "EncryptTable.h"

CEncryptOutputStream::CEncryptOutputStream(std::unique_ptr<IOutputDataStream>&& stream, size_t key)
	: COutputStreamDecorator(move(stream)), m_enctyptTable(256)
{
	m_enctyptTable = GenerateEncryptTable(key);
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
