#pragma once
#include "OutputStreamDecorator.h"
#include <vector>

class CEncryptOutputStream : public COutputStreamDecorator
{
public:
	CEncryptOutputStream(std::unique_ptr<IOutputDataStream>&& outputStream, size_t key);

	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;
private:
	std::vector<uint8_t> m_enctyptTable;
};