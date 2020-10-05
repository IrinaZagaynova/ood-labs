#include "InputStreamDecorator.h"
#include <iostream>

CInputStreamDecorator::CInputStreamDecorator(std::unique_ptr<IInputDataStream>&& stream)
	: m_stream(move(stream))
{
}

bool CInputStreamDecorator::IsEOF() const
{
	return m_stream->IsEOF();
}

uint8_t CInputStreamDecorator::ReadByte()
{
	return m_stream->ReadByte();
}

std::streamsize CInputStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	return m_stream->ReadBlock(dstBuffer, size);
}