#include "OutputStreamDecorator.h"

COutputStreamDecorator::COutputStreamDecorator(std::unique_ptr<IOutputDataStream>&& stream)
	: m_stream(move(stream))
{
}

void COutputStreamDecorator::WriteByte(uint8_t data)
{
	m_stream->WriteByte(data);
}

void COutputStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	m_stream->WriteBlock(srcData, size);
}

