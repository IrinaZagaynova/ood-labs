#pragma once
#include "InputStreamDecorator.h"

class CDecompressInputStream : public CInputStreamDecorator
{
public:
	CDecompressInputStream(std::unique_ptr<IInputDataStream>&& stream);
	bool IsEOF()const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	uint8_t m_counter = 0;
	uint8_t m_value = 0;
};
