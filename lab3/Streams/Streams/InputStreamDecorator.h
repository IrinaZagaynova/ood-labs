#pragma once
#include "IInputDataStream.h"
#include <memory>

class CInputStreamDecorator : public IInputDataStream
{
protected:
	CInputStreamDecorator(std::unique_ptr<IInputDataStream>&& inputStream)
		: m_stream(move(inputStream))
	{
	}
	virtual bool IsEOF()const = 0;
	virtual uint8_t ReadByte() = 0;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

protected:
	std::unique_ptr<IInputDataStream> m_stream;
};