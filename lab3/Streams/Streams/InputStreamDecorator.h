#pragma once
#include "IInputDataStream.h"
#include <memory>

class CInputStreamDecorator : public IInputDataStream
{
protected:
	CInputStreamDecorator(std::unique_ptr<IInputDataStream>&& inputStream);
	virtual bool IsEOF()const override;
	virtual uint8_t ReadByte() override;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

protected:
	std::unique_ptr<IInputDataStream> m_stream;
};