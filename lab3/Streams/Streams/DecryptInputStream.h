#pragma once
#include "InputStreamDecorator.h"
#include <vector>

class CDecryptInputStream : public CInputStreamDecorator
{
public:
	CDecryptInputStream(std::unique_ptr<IInputDataStream>&& stream, size_t key);
	bool IsEOF()const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	std::vector<uint8_t> m_dectyptTable;
};