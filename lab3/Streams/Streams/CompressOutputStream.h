#pragma once
#include "OutputStreamDecorator.h"

class CCompressOutputStream : public COutputStreamDecorator
{
public:
	CCompressOutputStream(std::unique_ptr<IOutputDataStream>&& stream);
	~CCompressOutputStream();

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	void FlushChunk();

private:
	uint8_t m_value = 0;
	uint8_t m_counter = 0;
};